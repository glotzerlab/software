set -u
set -e

usage="$(basename "$0") root -- Build software and install in root."

if [[ $# -lt 1 || $# -gt 1  || $1 == "-h" ]]
then
    echo "$usage"
    exit 0
fi

ROOT=$1
mkdir -p $ROOT

cat >$ROOT/environment.sh << EOL
module reset
module load gcc/4.8.5
module load python/3.7.0
module load cuda
module load py-numpy
module load cmake
module load git
module load py-pip
module load py-cython
module load py-h5py
module load py-mpi4py
module load py-nose
module load py-six
module load py-setuptools

export LD_LIBRARY_PATH=$ROOT/lib:\$LD_LIBRARY_PATH
export PATH=$ROOT/bin:\$PATH
export PYTHONPATH=$ROOT/lib/python3.7/site-packages:\$PYTHONPATH
export CPATH=$ROOT/include:\$CPATH
export LIBRARY_PATH=$ROOT/lib:\$LIBRARY_PATH
EOL

source $ROOT/environment.sh

mkdir -p /tmp/$USER
cd /tmp/$USER

# python3-scipy \

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





 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.11.3.tar.gz \
    && echo "fc803bd20a43b998cc660011ac408c51750427bebe5e26131aef9f9446fe53ec  freud-v0.11.3.tar.gz" | sha256sum -c - \
    && tar -xzf freud-v0.11.3.tar.gz -C . \
    && rm -f freud-v0.11.3/*.toml \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed --prefix=$ROOT ./freud-v0.11.3 \
    && rm -rf freud-v0.11.3 \
    && rm freud-v0.11.3.tar.gz \
    || exit 1



 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.5.4.tar.gz \
    && echo "09b09f1316c809dae96b1a02972673ef928eb549fcc1cae484265590a5b4acff  gsd-v1.5.4.tar.gz" | sha256sum -c - \
    && tar -xzf gsd-v1.5.4.tar.gz -C . \
    && cd gsd-v1.5.4 \
    && mkdir build \
    && cd build \
    && export CFLAGS="" CXXFLAGS="" \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=$ROOT`python -c "import distutils.sysconfig; print(distutils.sysconfig.get_python_lib()[len(distutils.sysconfig.PREFIX):])"` \
    && make install -j20 \
    && cd ../../ \
    && rm -rf gsd-v1.5.4 \
    && rm gsd-v1.5.4.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/libgetar/libgetar-v0.7.0.tar.gz \
    && echo "2a33809981b7a99c856ca60a1a7b9b1a0b3978fd8315ab3ab07b7b279a7c55e7  libgetar-v0.7.0.tar.gz" | sha256sum -c - \
    && tar -xzf libgetar-v0.7.0.tar.gz -C . \
    && rm -f libgetar-v0.7.0/*.toml \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed --prefix=$ROOT ./libgetar-v0.7.0 \
    && rm -rf libgetar-v0.7.0 \
    && rm libgetar-v0.7.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/rowan/rowan-v1.1.6.tar.gz \
    && echo "14627245b95b88e3d4358e6d9df0501eec1bcb892c71ba5829904d4728ecb9f8  rowan-v1.1.6.tar.gz" | sha256sum -c - \
    && tar -xzf rowan-v1.1.6.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed --prefix=$ROOT ./rowan-v1.1.6 \
    && rm -rf rowan-v1.1.6 \
    && rm rowan-v1.1.6.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/plato/plato-v1.2.0.tar.gz \
    && echo "fdd574a5ed6956bb68430de13991938d4765697736c857822c8c1addf5edd07d  plato-v1.2.0.tar.gz" | sha256sum -c - \
    && tar -xzf plato-v1.2.0.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed --prefix=$ROOT ./plato-v1.2.0 \
    && rm -rf plato-v1.2.0 \
    && rm plato-v1.2.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/pythia/pythia-v0.2.3.tar.gz \
    && echo "6fa74e608024d8126657d788016ec3a4112a7c17b8deda86e51a2905c47f5ed5  pythia-v0.2.3.tar.gz" | sha256sum -c - \
    && tar -xzf pythia-v0.2.3.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed --prefix=$ROOT ./pythia-v0.2.3 \
    && rm -rf pythia-v0.2.3 \
    && rm pythia-v0.2.3.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac/signac-v0.9.4.tar.gz \
    && echo "8a3c5b46d079decb9fa2d5d85628c2bd31057a44e945beba930d3b624dcb8437  signac-v0.9.4.tar.gz" | sha256sum -c - \
    && tar -xzf signac-v0.9.4.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed --prefix=$ROOT ./signac-v0.9.4 \
    && rm -rf signac-v0.9.4 \
    && rm signac-v0.9.4.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.6.3.tar.gz \
    && echo "0a1ff4d052ea1e02079b60c0a5710df28e3fa8286649ccc030d032ec99901dba  signac-flow-v0.6.3.tar.gz" | sha256sum -c - \
    && tar -xzf signac-flow-v0.6.3.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed --prefix=$ROOT ./signac-flow-v0.6.3 \
    && rm -rf signac-flow-v0.6.3 \
    && rm signac-flow-v0.6.3.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.4.0.tar.gz \
    && echo "052fffd0ebcc43a86fa530ff54054ae183dcd5c404957e41f7d83f633e39569a  hoomd-v2.4.0.tar.gz" | sha256sum -c - \
    && tar -xzf hoomd-v2.4.0.tar.gz -C . \
    && cd hoomd-v2.4.0 \
    && mkdir build \
    && cd build \
    && export CFLAGS="" CXXFLAGS="" \
    && cmake ../ -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=off -DBUILD_JIT=off -DBUILD_TESTING=off -DENABLE_MPI_CUDA=on -DCMAKE_INSTALL_PREFIX=$ROOT`python -c "import distutils.sysconfig; print(distutils.sysconfig.get_python_lib()[len(distutils.sysconfig.PREFIX):])"` \
    && make install -j20 \
    && cd ../../ \
    && rm -rf /root/hoomd-v2.4.0 \
    && rm hoomd-v2.4.0.tar.gz \
    || exit 1

