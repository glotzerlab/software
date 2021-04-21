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
python3 -m venv $ROOT --system-site-packages

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

python3 -m pip install --upgrade pip
python3 -m pip install --no-cache-dir --no-binary mpi4py -r requirements-mpi.txt

# TBB
curl -sSLO https://github.com/oneapi-src/oneTBB/archive/v2021.2.0.tar.gz \
    && tar -xzf v2021.2.0.tar.gz -C . \
    && cd oneTBB-2021.2.0 \
    && make \
    && install -d $ROOT/lib \
    && install -m755 build/linux_*release/*.so* ${ROOT}/lib \
    && install -d $ROOT/include \
    && cp -a include/tbb $ROOT/include \
    && cd .. \
    && rm -rf oneTBB-2021.2.0 \
    && rm v2021.2.0.tar.gz \
    || exit 1

# embree is not available for power9

# install pybind11 headers
curl -SL https://github.com/pybind/pybind11/archive/v2.6.2.tar.gz | tar -xzC $BUILDDIR && \
    cd pybind11-2.6.2 && \
    mkdir build && cd build && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DPYBIND11_TEST=off && \
    make install && \
    cd $BUILDDIR && rm -rf pybind11-*

# install cereal headers
curl -SL https://github.com/USCiLab/cereal/archive/v.tar.gz | tar -xzC $BUILDDIR && \
    cd cereal- && \
    mkdir build && cd build && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DJUST_INSTALL_CEREAL=on && \
    make install && \
    cd $BUILDDIR && rm -rf cereal-*

# install eigen headers
curl -SL https://gitlab.com/libeigen/eigen/-/archive//eigen-.tar.gz | tar -xzC $BUILDDIR && \
    cd eigen- && \
    mkdir build && cd build && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DBUILD_TESTING=off, -DEIGEN_TEST_NOQT=on && \
    make install && \
    cd $BUILDDIR && rm -rf eigen-*




# build scipy from source on summit
 export LAPACK=${OLCF_NETLIB_LAPACK_ROOT}/lib64/liblapack.so BLAS=${OLCF_NETLIB_LAPACK_ROOT}/lib64/libblas.so
    && python3 -m pip install \
       --no-cache-dir \
       --no-binary freud-analysis,gsd,scipy,numpy \
       -r requirements.txt \
    || exit 1


RUN python3 -m pip install \
    --no-cache-dir \
    -r requirements.txt



 git clone --recursive --branch v2.9.6 --depth 1 https://github.com/glotzerlab/hoomd-blue hoomd \
    && cd hoomd \
    && mkdir -p build \
    && cd build \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_GPU=on -DENABLE_MPI=on -DENABLE_TBB=off -DBUILD_JIT=off -DBUILD_TESTING=off -DENABLE_MPI_CUDA=on \
    && make install -j4 \
    && cd ../../ \
    && rm -rf hoomd \
    || exit 1