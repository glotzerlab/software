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
ROOT=$(realpath $1)
echo "Installing glotzerlab-software to $ROOT"
module reset
module load gcc/7.5.0
module load python/3.8.10
python3 -m venv $ROOT

cat >$ROOT/environment.sh << EOL
module reset
module load gcc/7.5.0
module load openblas/0.3.20
module load python/3.8.10
module load cuda/11.0.3
module load cmake
module load git
module load netlib-lapack/3.9.1
module load hdf5/1.10.7
module unload darshan-runtime

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
# setuptools <60 needed to build scipy 1.9.3 from source
python3 -m pip install --upgrade pip setuptools==59.8.0 wheel
python3 -m pip install -r requirements-mpi.txt

# TBB
if [ ! -f $ROOT/lib64/libtbb.so ]
then
curl -sSLO https://github.com/oneapi-src/oneTBB/archive/v2021.10.0.tar.gz \
    && tar -xzf v2021.10.0.tar.gz -C . \
    && cd oneTBB-2021.10.0 \
    && cmake -S . -B build -DTBB_TEST=off -DTBB_STRICT=off -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$ROOT \
    && cmake --build build -j 8  \
    && cmake --install build \
    && cd .. \
    && rm -rf oneTBB-2021.10.0 \
    && rm v2021.10.0.tar.gz \
    || exit 1
fi

# embree is not available for power9

# install pybind11 headers
if [ ! -f $ROOT/include/pybind11/pybind11.h ]
then
curl -SL https://github.com/pybind/pybind11/archive/v2.11.1.tar.gz | tar -xzC $BUILDDIR && \
    cd pybind11-2.11.1 && \
    mkdir build && cd build && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DPYBIND11_TEST=off && \
    make install && \
    cd $BUILDDIR && rm -rf pybind11-*
fi

# install cereal headers
if [ ! -f $ROOT/include/cereal/cereal.hpp ]
then
curl -SL https://github.com/USCiLab/cereal/archive/v1.3.2.tar.gz | tar -xzC $BUILDDIR && \
    cd cereal-1.3.2 && \
    mkdir build && cd build && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DJUST_INSTALL_CEREAL=on && \
    make install && \
    cd $BUILDDIR && rm -rf cereal-*
fi

# install eigen headers
if [ ! -f $ROOT/include/eigen3/Eigen/Eigen ]
then
curl -SL https://gitlab.com/libeigen/eigen/-/archive/3.4.0/eigen-3.4.0.tar.gz | tar -xzC $BUILDDIR && \
    cd eigen-3.4.0 && \
    mkdir build && cd build && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DBUILD_TESTING=off, -DEIGEN_TEST_NOQT=on && \
    make install && \
    cd $BUILDDIR && rm -rf eigen-*
fi

if [ ! -f $ROOT/bin/clang ]
then
    git clone --depth 1 --branch release/12.x https://github.com/llvm/llvm-project
    cd llvm-project
    cmake -S llvm -B build \
        -D CMAKE_INSTALL_PREFIX=$ROOT -DLLVM_ENABLE_PROJECTS=clang \
        -DCLANG_LINK_CLANG_DYLIB=ON \
        -DLLVM_BUILD_LLVM_DYLIB=ON \
        -DLLVM_LINK_LLVM_DYLIB=ON \
        -DCMAKE_BUILD_TYPE=Release \
        -DLLVM_TARGETS_TO_BUILD="PowerPC"
    cmake --build build -j 8
    cmake --install build
    cd $BUILDDIR
    rm -rf llvm-project
fi





# Install packages that are build requirements of other packages first.
# Use the pip cache in script builds to reduce time when rerunning the install script.


 export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9"
while read package; do
  python3 -m pip install --no-build-isolation $package || exit 1
done <requirements-source-summit.txt

 # modern setuptools needed for gsd and other packages\
 python3 -m pip install --upgrade setuptools


 export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-build-isolation --no-binary freud-analysis,gsd -r requirements.txt \
    || exit 1


 export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-build-isolation -r requirements-cupy.txt \
    || exit 1








if [ ! -n "$(ls -d $ROOT/lib/python*/site-packages/hoomd)" ]
then

 git clone --recursive --branch v4.1.0 --depth 1 https://github.com/glotzerlab/hoomd-blue hoomd \
    && cd hoomd \
    && mkdir -p build \
    && cd build \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_GPU=on -DENABLE_MPI=on -DENABLE_TBB=off -DENABLE_LLVM=on -DBUILD_TESTING=off -DENABLE_MPI_CUDA=off -DHOOMD_GPU_PLATFORM=CUDA \
    && make install -j8 \
    && cd ../../ \
    && rm -rf hoomd \
    || exit 1


fi
