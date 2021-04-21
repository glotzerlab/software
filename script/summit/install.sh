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
EOL

source $ROOT/environment.sh

mkdir -p /tmp/$USER-glotzerlab-software
cp -a $DIR/../../*.txt /tmp/$USER-glotzerlab-software
cd /tmp/$USER-glotzerlab-software

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
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=off -DBUILD_JIT=off -DBUILD_TESTING=off -DENABLE_MPI_CUDA=on -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j4 \
    && cd ../../ \
    && rm -rf hoomd \
    || exit 1