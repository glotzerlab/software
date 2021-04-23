#!/usr/bin/bash

set -u
set -e

usage="$(basename "$0") root -- Build software and install in root."

if [[ $# -lt 1 || $# -gt 1  || $1 == "-h" ]]
then
    echo "$usage"
    exit 0
fi

DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
ROOT=$1
module reset
module load gcc/7.4.0
module load python/3.7.0
python3 -m venv $ROOT

cat >$ROOT/environment.sh << EOL
module reset
module load gcc/7.4.0
module load cuda
module load cmake
module load git
module load netlib-lapack/3.8.0
module load hdf5/1.10.3

export LD_LIBRARY_PATH=$ROOT/lib:\$LD_LIBRARY_PATH
export PATH=$ROOT/bin:\$PATH
export CPATH=$ROOT/include:\$CPATH
export LIBRARY_PATH=$ROOT/lib:\$LIBRARY_PATH
export CC=\${OLCF_GCC_ROOT}/bin/gcc
export CXX=\${OLCF_GCC_ROOT}/bin/g++
export LDSHARED="\${OLCF_GCC_ROOT}/bin/gcc -shared"
export VIRTUAL_ENV=$ROOT
export CMAKE_PREFIX_PATH=$ROOT
EOL

source $ROOT/environment.sh

BUILDDIR=`mktemp -d`
mkdir -p $BUILDDIR

# deletes the temp directory
function cleanup {
  rm -rf "$BUILDDIR"
  echo "Deleted temp working directory $BUILDDIR"
}

trap cleanup EXIT
cd $BUILDDIR

cp -a $DIR/../../*.txt $BUILDDIR
cd $BUILDDIR

set -x
python3 -m pip install --upgrade pip setuptools wheel
python3 -m pip install -r requirements-mpi.txt

exit 1

# TBB
if [ ! -f $ROOT/lib64/libtbb.so ]
then
curl -sSLO https://github.com/oneapi-src/oneTBB/archive/v2021.2.0.tar.gz \
    && tar -xzf v2021.2.0.tar.gz -C . \
    && cd oneTBB-2021.2.0 \
    && cmake -S . -B build -DTBB_TEST=off -DTBB_STRICT=off -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$ROOT \
    && cmake --build build -j 4  \
    && cmake --install build \
    && cd .. \
    && rm -rf oneTBB-2021.2.0 \
    && rm v2021.2.0.tar.gz \
    || exit 1
fi

# embree is not available for power9

# install pybind11 headers
if [ ! -f $ROOT/include/pybind11/pybind11.h ]
then
curl -SL https://github.com/pybind/pybind11/archive/v2.6.2.tar.gz | tar -xzC $BUILDDIR && \
    cd pybind11-2.6.2 && \
    mkdir build && cd build && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DPYBIND11_TEST=off && \
    make install && \
    cd $BUILDDIR && rm -rf pybind11-*
fi

# install cereal headers
if [ ! -f $ROOT/include/cereal/cereal.hpp ]
then
curl -SL https://github.com/USCiLab/cereal/archive/v1.3.0.tar.gz | tar -xzC $BUILDDIR && \
    cd cereal-1.3.0 && \
    mkdir build && cd build && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DJUST_INSTALL_CEREAL=on && \
    make install && \
    cd $BUILDDIR && rm -rf cereal-*
fi

# install eigen headers
if [ ! -f $ROOT/include/eigen3/Eigen/Eigen ]
then
curl -SL https://gitlab.com/libeigen/eigen/-/archive/3.3.9/eigen-3.3.9.tar.gz | tar -xzC $BUILDDIR && \
    cd eigen-3.3.9 && \
    mkdir build && cd build && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DBUILD_TESTING=off, -DEIGEN_TEST_NOQT=on && \
    make install && \
    cd $BUILDDIR && rm -rf eigen-*
fi






# install scipy first - otherwise scikit-learn fails to build
 export LAPACK=${OLCF_NETLIB_LAPACK_ROOT}/lib64/liblapack.so BLAS=${OLCF_NETLIB_LAPACK_ROOT}/lib64/libblas.so \
    && python3 -m pip intstall scipy scipy

# unlike with Docker builds, use the pip cache on summit to reduce time when rerunning the install script
 python3 -m pip install -r requirements.txt \
    || exit 1





 git clone --recursive --branch v3.0.0-beta.5 --depth 1 https://github.com/glotzerlab/hoomd-blue hoomd \
    && cd hoomd \
    && mkdir -p build \
    && cd build \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_GPU=on -DENABLE_MPI=on -DENABLE_TBB=off -DBUILD_JIT=off -DBUILD_TESTING=off -DENABLE_MPI_CUDA=on \
    && make install -j4 \
    && cd ../../ \
    && rm -rf hoomd \
    || exit 1