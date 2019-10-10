#!/usr/bin/bash

set -u
set -e

usage="$(basename "$0") root -- Build software and install in root."

if [[ $# -lt 1 || $# -gt 1  || $1 == "-h" ]]
then
    echo "$usage"
    exit 0
fi

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
cd /tmp/$USER-glotzerlab-software

python3 -m pip install --progress-bar off --no-deps --no-binary :all: cython mpi4py six numpy tables numexpr deprecation

# TBB
curl -sSLO https://github.com/01org/tbb/archive/2019_U8.tar.gz \
    && echo "7b1fd8caea14be72ae4175896510bf99c809cd7031306a1917565e6de7382fba  2019_U8.tar.gz" | sha256sum -c - \
    && tar -xzf 2019_U8.tar.gz -C . \
    && cd tbb-2019_U8 \
    && make \
    && install -d $ROOT/lib \
    && install -m755 build/linux_*release/*.so* ${ROOT}/lib \
    && install -d $ROOT/include \
    && cp -a include/tbb $ROOT/include \
    && cd .. \
    && rm -rf tbb-2019_U8 \
    && rm 2019_U8.tar.gz \
    || exit 1

# embree is not available for power9

# scipy
curl -sSLO https://github.com/scipy/scipy/releases/download/v1.3.1/scipy-1.3.1.tar.gz \
    && echo "2643cfb46d97b7797d1dbdb6f3c23fe3402904e3c90e6facfe6a9b98d808c1b5  scipy-1.3.1.tar.gz" | sha256sum -c - \
    && tar -xzf scipy-1.3.1.tar.gz -C . \
    && cd scipy-1.3.1 \
    && LAPACK=${OLCF_NETLIB_LAPACK_ROOT}/lib64/liblapack.so BLAS=${OLCF_NETLIB_LAPACK_ROOT}/lib64/libblas.so python3 setup.py install \
    && rm -rf scipy-1.3.1 \
    || exit 1



 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v1.2.2.tar.gz \
    && echo "53e58f157be07e6fcf90431c19188874c5cba9ac48bffc19f631930d176b6c9d  freud-v1.2.2.tar.gz" | sha256sum -c - \
    && tar -xzf freud-v1.2.2.tar.gz -C . \
    && rm -f freud-v1.2.2/*.toml \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./freud-v1.2.2 \
    && rm -rf freud-v1.2.2 \
    && rm freud-v1.2.2.tar.gz \
    || exit 1



 curl -sSLO https://glotzerlab.engin.umich.edu/downloads/garnett/garnett-v0.5.0.tar.gz \
    && echo "9be24f8332757c00945849784316b06a2db58f06569a988bfb88c0af6455df1f  garnett-v0.5.0.tar.gz" | sha256sum -c - \
    && tar -xzf garnett-v0.5.0.tar.gz -C . \
    && rm -f garnett-v0.5.0/*.toml \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./garnett-v0.5.0 \
    && rm -rf garnett-v0.5.0 \
    && rm garnett-v0.5.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.9.3.tar.gz \
    && echo "89db85565b87d7a167ecf01881382ec4bc7280f07fe0295c2cf74af5db949231  gsd-v1.9.3.tar.gz" | sha256sum -c - \
    && tar -xzf gsd-v1.9.3.tar.gz -C . \
    && cd gsd-v1.9.3 \
    && mkdir -p build \
    && cd build \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j20 \
    && cd ../../ \
    && rm -rf gsd-v1.9.3 \
    && rm gsd-v1.9.3.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/libgetar/libgetar-v1.0.1.tar.gz \
    && echo "0a438dc8336103158fc4dbb7ebcbc011279d7a8ae134824dda5946e6b9042039  libgetar-v1.0.1.tar.gz" | sha256sum -c - \
    && tar -xzf libgetar-v1.0.1.tar.gz -C . \
    && rm -f libgetar-v1.0.1/*.toml \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./libgetar-v1.0.1 \
    && rm -rf libgetar-v1.0.1 \
    && rm libgetar-v1.0.1.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/rowan/rowan-v1.2.2.tar.gz \
    && echo "88ed2c0003543d3154374f741a04fcb21cce32180e7b29152dc93c4c887e0c51  rowan-v1.2.2.tar.gz" | sha256sum -c - \
    && tar -xzf rowan-v1.2.2.tar.gz -C . \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./rowan-v1.2.2 \
    && rm -rf rowan-v1.2.2 \
    && rm rowan-v1.2.2.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/plato/plato-v1.7.0.tar.gz \
    && echo "8268ab6982f9135d1f7788309804eb15a1e98ef1d2f6d959733a3e23a1595def  plato-v1.7.0.tar.gz" | sha256sum -c - \
    && tar -xzf plato-v1.7.0.tar.gz -C . \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./plato-v1.7.0 \
    && rm -rf plato-v1.7.0 \
    && rm plato-v1.7.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/pythia/pythia-v0.2.5.tar.gz \
    && echo "5dfe1efeb7343fbfc7260dc6f05a8ee17908add288c67094d3740c7056627140  pythia-v0.2.5.tar.gz" | sha256sum -c - \
    && tar -xzf pythia-v0.2.5.tar.gz -C . \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./pythia-v0.2.5 \
    && rm -rf pythia-v0.2.5 \
    && rm pythia-v0.2.5.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac/signac-v1.2.0.tar.gz \
    && echo "38591f2c0dcb77d28dfeb7906b2c25bfc3df39d67486ff819872ba69be4fa187  signac-v1.2.0.tar.gz" | sha256sum -c - \
    && tar -xzf signac-v1.2.0.tar.gz -C . \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-v1.2.0 \
    && rm -rf signac-v1.2.0 \
    && rm signac-v1.2.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.8.0.tar.gz \
    && echo "ae933964e2786f22963f70ff147a2cbd152e7e32c903ba550154b91db890451b  signac-flow-v0.8.0.tar.gz" | sha256sum -c - \
    && tar -xzf signac-flow-v0.8.0.tar.gz -C . \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-flow-v0.8.0 \
    && rm -rf signac-flow-v0.8.0 \
    && rm signac-flow-v0.8.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.7.0.tar.gz \
    && echo "f884583b4d16bc630e177aefc198fb8361e644f6cad1b0c0474e840f00a4e4e1  hoomd-v2.7.0.tar.gz" | sha256sum -c - \
    && tar -xzf hoomd-v2.7.0.tar.gz -C . \
    && cd hoomd-v2.7.0 \
    && mkdir -p build \
    && cd build \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=off -DBUILD_JIT=off -DBUILD_TESTING=off -DENABLE_MPI_CUDA=on -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j20 \
    && cd ../../ \
    && rm -rf /root/hoomd-v2.7.0 \
    && rm hoomd-v2.7.0.tar.gz \
    || exit 1

