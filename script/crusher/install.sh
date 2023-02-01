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
module load cray-python/3.9.13.1
python3 -m venv $ROOT

cat >$ROOT/environment.sh << EOL
module reset
module load cmake/3.23.2
module load git/2.36.1
module load rocm/5.1.0
module load cray-python/3.9.13.1
module load hdf5/1.12.1

# The cray-mpich module does not provide this, it is needed to build mpi4py from source.
export MPICC=\$CRAY_MPICH_DIR/bin/mpicc

export LD_LIBRARY_PATH=$ROOT/lib:\$LD_LIBRARY_PATH
export PATH=$ROOT/bin:\$PATH
export CPATH=$ROOT/include
export LIBRARY_PATH=$ROOT/lib
export VIRTUAL_ENV=$ROOT
export CMAKE_PREFIX_PATH=$ROOT

# Settings to build cupy for rocm: https://docs.cupy.dev/en/stable/install.html
export CUPY_INSTALL_USE_HIP=1
export ROCM_HOME=\$OLCF_ROCM_ROOT
export HCC_AMDGPU_TARGET=gfx90a
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

# TBB
if [ ! -f $ROOT/lib64/libtbb.so ]
then
curl -sSLO https://github.com/oneapi-src/oneTBB/archive/v2021.8.0.tar.gz \
    && tar -xzf v2021.8.0.tar.gz -C . \
    && cd oneTBB-2021.8.0 \
    && cmake -S . -B build -DTBB_TEST=off -DTBB_STRICT=off -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$ROOT \
    && cmake --build build -j 16  \
    && cmake --install build \
    && cd .. \
    && rm -rf oneTBB-2021.8.0 \
    && rm v2021.8.0.tar.gz \
    || exit 1
fi

# Embree
if [ ! -f $ROOT/lib64/libembree3.so ]
then
curl -sSL https://github.com/embree/embree/archive/v3.13.5/embree-3.13.5.tar.gz | tar -xzC $BUILDDIR \
    && cd $BUILDDIR/embree-3.13.5 \
    && mkdir build && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DCMAKE_INSTALL_LIBDIR=lib64/ -DCMAKE_BUILD_TYPE=Release -DEMBREE_TUTORIALS=OFF -DEMBREE_MAX_ISA="AVX2" -DEMBREE_ISPC_SUPPORT=OFF \
    && make install -j 16 \
    && cd $BUILDDIR/ && rm -rf embree-*
fi

# install pybind11 headers
if [ ! -f $ROOT/include/pybind11/pybind11.h ]
then
curl -SL https://github.com/pybind/pybind11/archive/v2.10.3.tar.gz | tar -xzC $BUILDDIR && \
    cd pybind11-2.10.3 && \
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

# if [ ! -f $ROOT/bin/clang ]
# then
#     git clone --depth 1 --branch release/12.x https://github.com/llvm/llvm-project
#     cd llvm-project
#     cmake -S llvm -B build \
#         -D CMAKE_INSTALL_PREFIX=$ROOT -DLLVM_ENABLE_PROJECTS=clang \
#         -DCLANG_LINK_CLANG_DYLIB=ON \
#         -DLLVM_BUILD_LLVM_DYLIB=ON \
#         -DLLVM_LINK_LLVM_DYLIB=ON \
#         -DCMAKE_BUILD_TYPE=Release \
#         -DLLVM_TARGETS_TO_BUILD="PowerPC"
#     cmake --build build -j 16
#     cmake --install build
#     cd $BUILDDIR
#     rm -rf llvm-project
# fi





# Install packages that are build requirements of other packages first.
# lapack is needed for scipy.
# Use the pip cache in script builds to reduce time when rerunning the install script.
 export CFLAGS="-march=native" CXXFLAGS="-march=native"\
    && python3 -m pip install -r requirements-source.txt \
    || exit 1

 export CFLAGS="-march=native" CXXFLAGS="-march=native" \
    && python3 -m pip install --no-build-isolation -r requirements.txt \
    || exit 1




 git clone --recursive --branch v0.13.4 --depth 1 https://github.com/glotzerlab/fresnel \
    && cd fresnel \
    && mkdir -p build \
    && cd build \
    && export CFLAGS="-march=native" CXXFLAGS="-march=native" \
    && cmake ../ -DENABLE_EMBREE=on -DENABLE_OPTIX=off -Dembree_DIR=/opt/embree-3.13.5.x86_64.linux -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j16 \
    && cd ../../ \
    && rm -rf fresnel \
    || exit 1

 git clone --recursive --branch fix-rocm-build --depth 1 https://github.com/glotzerlab/hoomd-blue hoomd \
    && cd hoomd \
    && mkdir -p build \
    && cd build \
    && export CFLAGS="-march=native" CXXFLAGS="-march=native" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_GPU=on -DENABLE_MPI=on -DENABLE_TBB=off -DENABLE_LLVM=off -DBUILD_TESTING=off -DENABLE_MPI_CUDA=off -DHOOMD_GPU_PLATFORM=HIP \
    && make install -j16 \
    && cd ../../ \
    && rm -rf hoomd \
    || exit 1