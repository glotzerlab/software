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
module load gcc/4.8.5
module load python/3.7.0
python3 -m venv $ROOT --system-site-packages

cat >$ROOT/environment.sh << EOL
module reset
module load gcc/6.4.0
module load cuda
module load cmake
module load git

export LD_LIBRARY_PATH=$ROOT/lib:\$LD_LIBRARY_PATH
export PATH=$ROOT/bin:\$PATH
export CPATH=$ROOT/include:\$CPATH
export LIBRARY_PATH=$ROOT/lib:\$LIBRARY_PATH
export CC=\${OLCF_GCC_ROOT}/bin/gcc
export CXX=\${OLCF_GCC_ROOT}/bin/g++
export VIRTUAL_ENV=$ROOT
EOL

source $ROOT/environment.sh

mkdir -p /tmp/$USER-glotzerlab-software
cd /tmp/$USER-glotzerlab-software
rm -rf /tmp/$USER-glotzerlab-software/*

python3 -m pip install --progress-bar off --no-deps --no-binary :all: cython mpi4py six numpy

# TBB
curl -sSLO https://github.com/01org/tbb/archive/2019_U2.tar.gz \
    && echo "1245aa394a92099e23ce2f60cdd50c90eb3ddcd61d86cae010ef2f1de61f32d9  2019_U2.tar.gz" | sha256sum -c - \
    && tar -xzf 2019_U2.tar.gz -C . \
    && cd tbb-2019_U2 \
    && make \
    && install -d $ROOT/lib \
    && install -m755 build/linux_*release/*.so* ${ROOT}/lib \
    && install -d $ROOT/include \
    && cp -a include/tbb $ROOT/include \
    && cd .. \
    && rm -rf tbb-2019_U2 \
    && rm 2019_U2.tar.gz \
    || exit 1

# embree is not available for power9



 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.11.4.tar.gz \
    && echo "9e54cb2f9ef2df7569ae04b5794d0372439b8667cd1ba32390496b5ddf3ad233  freud-v0.11.4.tar.gz" | sha256sum -c - \
    && tar -xzf freud-v0.11.4.tar.gz -C . \
    && rm -f freud-v0.11.4/*.toml \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./freud-v0.11.4 \
    && rm -rf freud-v0.11.4 \
    && rm freud-v0.11.4.tar.gz \
    || exit 1



 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.6.0.tar.gz \
    && echo "2d4ddacbea75b36a446a41c5df8ba16d793c5f1674e001795393931f96d0f4e9  gsd-v1.6.0.tar.gz" | sha256sum -c - \
    && tar -xzf gsd-v1.6.0.tar.gz -C . \
    && cd gsd-v1.6.0 \
    && mkdir build \
    && cd build \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j20 \
    && cd ../../ \
    && rm -rf gsd-v1.6.0 \
    && rm gsd-v1.6.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/libgetar/libgetar-v0.7.0.tar.gz \
    && echo "2a33809981b7a99c856ca60a1a7b9b1a0b3978fd8315ab3ab07b7b279a7c55e7  libgetar-v0.7.0.tar.gz" | sha256sum -c - \
    && tar -xzf libgetar-v0.7.0.tar.gz -C . \
    && rm -f libgetar-v0.7.0/*.toml \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./libgetar-v0.7.0 \
    && rm -rf libgetar-v0.7.0 \
    && rm libgetar-v0.7.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/rowan/rowan-v1.1.6.tar.gz \
    && echo "14627245b95b88e3d4358e6d9df0501eec1bcb892c71ba5829904d4728ecb9f8  rowan-v1.1.6.tar.gz" | sha256sum -c - \
    && tar -xzf rowan-v1.1.6.tar.gz -C . \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./rowan-v1.1.6 \
    && rm -rf rowan-v1.1.6 \
    && rm rowan-v1.1.6.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/plato/plato-v1.4.0.tar.gz \
    && echo "fd5b764da5fdca9e704b22629b12c83fbf482db95fe7050e2b7b7661c8e57cdf  plato-v1.4.0.tar.gz" | sha256sum -c - \
    && tar -xzf plato-v1.4.0.tar.gz -C . \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./plato-v1.4.0 \
    && rm -rf plato-v1.4.0 \
    && rm plato-v1.4.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/pythia/pythia-v0.2.4.tar.gz \
    && echo "cebc1033759f518aa4f9c41d4660c7748b646f6f6117be9e4dcb9e53ef2f0251  pythia-v0.2.4.tar.gz" | sha256sum -c - \
    && tar -xzf pythia-v0.2.4.tar.gz -C . \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./pythia-v0.2.4 \
    && rm -rf pythia-v0.2.4 \
    && rm pythia-v0.2.4.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac/signac-v0.9.4.tar.gz \
    && echo "8a3c5b46d079decb9fa2d5d85628c2bd31057a44e945beba930d3b624dcb8437  signac-v0.9.4.tar.gz" | sha256sum -c - \
    && tar -xzf signac-v0.9.4.tar.gz -C . \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-v0.9.4 \
    && rm -rf signac-v0.9.4 \
    && rm signac-v0.9.4.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.6.4.tar.gz \
    && echo "c261204eef08c5e954179840cdb68795f2a464c213b58e67d7b502caada4d34c  signac-flow-v0.6.4.tar.gz" | sha256sum -c - \
    && tar -xzf signac-flow-v0.6.4.tar.gz -C . \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-flow-v0.6.4 \
    && rm -rf signac-flow-v0.6.4 \
    && rm signac-flow-v0.6.4.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.4.2.tar.gz \
    && echo "2d46725844336c9b3cd39fcba26741042410e9d20384d5218c9272c92cccfb08  hoomd-v2.4.2.tar.gz" | sha256sum -c - \
    && tar -xzf hoomd-v2.4.2.tar.gz -C . \
    && cd hoomd-v2.4.2 \
    && mkdir build \
    && cd build \
    && export CFLAGS="-mcpu=power9 -mtune=power9" CXXFLAGS="-mcpu=power9 -mtune=power9" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=off -DBUILD_JIT=off -DBUILD_TESTING=off -DENABLE_MPI_CUDA=on -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j20 \
    && cd ../../ \
    && rm -rf /root/hoomd-v2.4.2 \
    && rm hoomd-v2.4.2.tar.gz \
    || exit 1

