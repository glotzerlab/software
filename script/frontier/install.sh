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
module purge
module load PrgEnv-gnu
module load cray-python/3.10.10
python3 -m venv $ROOT

cat >$ROOT/variables.sh << EOL
module purge
module load PrgEnv-gnu
module load cmake/3.23.2
module load git/2.36.1
module load rocm/5.4.3
module load cray-python/3.10.10
module load hdf5/1.14.0
module load ninja/1.10.2
module load tmux/3.2a
module unload darshan-runtime

# The cray-mpich module does not provide this, it is needed to build mpi4py from source.
export MPICC=\$CRAY_MPICH_DIR/bin/mpicc

export LD_LIBRARY_PATH=\$GLOTZERLAB_SOFTWARE_ROOT/lib:\$LD_LIBRARY_PATH
export PATH=\$GLOTZERLAB_SOFTWARE_ROOT/bin:\$PATH
export CPATH=\$GLOTZERLAB_SOFTWARE_ROOT/include
export LIBRARY_PATH=\$GLOTZERLAB_SOFTWARE_ROOT/lib
export VIRTUAL_ENV=\$GLOTZERLAB_SOFTWARE_ROOT
export CMAKE_PREFIX_PATH=\$GLOTZERLAB_SOFTWARE_ROOT
export PYTHONPATH=\$(\${GLOTZERLAB_SOFTWARE_ROOT}/bin/python -c 'import site; print(site.getsitepackages()[0])')
export CC=\$GCC_PATH/bin/gcc
export CXX=\$GCC_PATH/bin/g++

# Settings to build cupy for rocm: https://docs.cupy.dev/en/stable/install.html
export CUPY_INSTALL_USE_HIP=1
export ROCM_HOME=\$OLCF_ROCM_ROOT
export HCC_AMDGPU_TARGET=gfx90a

export PYTHONUNBUFFERED=1

# work around PMI_Init mmap sync errors
export PMI_MMAP_SYNC_WAIT_TIME=1800
EOL

cat >$ROOT/environment.sh << EOL
export GLOTZERLAB_SOFTWARE_ROOT=$ROOT
source \$GLOTZERLAB_SOFTWARE_ROOT/variables.sh
EOL

cat >$ROOT/generate-tar-cache.sh << EOL
#! /usr/bin/bash
usage="\$(basename "\$0") output-file -- Generate a tar cache file."

if [[ \$# -lt 1 || \$# -gt 1  || \$1 == "-h" ]]
then
    echo "\$usage"
    exit 0
fi

DEST=\$(realpath \$1)

tar --directory $ROOT --exclude software.tar -cf \$DEST .
EOL
chmod ug+x $ROOT/generate-tar-cache.sh

source $ROOT/environment.sh

set -x

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
curl -sSLO https://github.com/oneapi-src/oneTBB/archive/v2021.11.0.tar.gz \
    && tar -xzf v2021.11.0.tar.gz -C . \
    && cd oneTBB-2021.11.0 \
    && cmake -S . -B build -DTBB_TEST=off -DTBB_STRICT=off -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=$ROOT \
    && cmake --build build -j 32  \
    && cmake --install build \
    && cd .. \
    && rm -rf oneTBB-2021.11.0 \
    && rm v2021.11.0.tar.gz \
    || exit 1
fi

# Embree
if [ ! -f $ROOT/lib64/libembree4.so ]
then
curl -sSL https://github.com/embree/embree/archive/v4.3.0/embree-4.3.0.tar.gz | tar -xzC $BUILDDIR \
    && cd $BUILDDIR/embree-4.3.0 \
    && mkdir build && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT -DCMAKE_INSTALL_LIBDIR=lib64/ -DCMAKE_BUILD_TYPE=Release -DEMBREE_TUTORIALS=OFF -DEMBREE_MAX_ISA="AVX2" -DEMBREE_ISPC_SUPPORT=OFF \
    && make install -j 32 \
    && cd $BUILDDIR/ && rm -rf embree-*
fi

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





# Install packages that are build requirements of other packages first.
# Use the pip cache in script builds to reduce time when rerunning the install script.

 export CFLAGS="-march=native" CXXFLAGS="-march=native"\
    && python3 -m pip install -r requirements-source.txt \
    || exit 1

 export CFLAGS="-march=native" CXXFLAGS="-march=native" \
    && python3 -m pip install --no-build-isolation --no-binary freud-analysis,gsd -r requirements.txt \
    && chmod o+rX `python3 -c "import site; print(site.getsitepackages()[0])"`/flow/templates/* \
    || exit 1






if [ ! -n "$(ls -d $ROOT/lib/python*/site-packages/fresnel)" ]
then

 git clone --recursive --branch v0.13.5 --depth 1 https://github.com/glotzerlab/fresnel \
    && cd fresnel \
    && mkdir -p build \
    && cd build \
    && export CFLAGS="-march=native" CXXFLAGS="-march=native" \
    && cmake ../ -DENABLE_EMBREE=on -DENABLE_OPTIX=off -Dembree_DIR=/opt/embree-4.3.0.x86_64.linux -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j32 \
    && cd ../../ \
    && rm -rf fresnel \
    || exit 1


fi



if [ ! -n "$(ls -d $ROOT/lib/python*/site-packages/hoomd)" ]
then

 git clone --recursive --branch v4.4.1 --depth 1 https://github.com/glotzerlab/hoomd-blue hoomd \
    && cd hoomd \
    && mkdir -p build \
    && cd build \
    && export CFLAGS="-march=native" CXXFLAGS="-march=native" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_GPU=on -DENABLE_MPI=on -DENABLE_TBB=off -DENABLE_LLVM=off -DBUILD_TESTING=off -DENABLE_MPI_CUDA=off -DHOOMD_GPU_PLATFORM=HIP \
    && make install -j32 \
    && cd ../../ \
    && rm -rf hoomd \
    || exit 1


fi
