FROM nvidia/cuda:9.2-devel-ubuntu16.04

RUN apt-get update && apt-get install -y --no-install-recommends \
  clang-5.0 \
  cmake \
  curl \
  cython3 \
  ffmpeg \
  git \
  libboost-dev \
  libedit-dev \
  libtbb-dev \
  libsqlite3-dev \
  llvm-5.0-dev \
  python3 \
  python3-dev \
  python3-h5py \
  python3-matplotlib \
  python3-nose \
  python3-numpy \
  python3-pandas \
  python3-pip \
  python3-pytest \
  python3-pyqt5 \
  python3-scipy \
  python3-sklearn-lib \
  python3-sklearn-pandas \
  python3-skimage-lib \
  python3-setuptools \
  python3-sphinx \
  python3-sphinx-rtd-theme \
  python3-yaml \
  zlib1g-dev \
  ca-certificates \
  && rm -rf /var/lib/apt/lists/* \
  && pip3 install --no-cache-dir jupyter pillow pyhull

# prevent python from loading packages from outside the container
# default empty pythonpath
ENV PYTHONPATH=/ignore/pythonpath
# disable user site directories (https://docs.python.org/3/library/site.html#module-site)
RUN sed -i -e 's/ENABLE_USER_SITE = None/ENABLE_USER_SITE = False/g' `python3 -c 'import site; print(site.__file__)'`

# put clang on the path
ENV PATH=$PATH:/usr/lib/llvm-5.0/bin

# embree
ENV CPATH=/opt/embree-3.5.2.x86_64.linux/include:$CPATH \
    LIBRARY_PATH=/opt/embree-3.5.2.x86_64.linux/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=/opt/embree-3.5.2.x86_64.linux/lib:$LD_LIBRARY_PATH \
    EMBREE3_LINK=/opt/embree-3.5.2.x86_64.linux/lib

RUN curl -sSLO https://github.com/embree/embree/releases/download/v3.5.2/embree-3.5.2.x86_64.linux.tar.gz \
    && echo "a2f2adf05db1ee3fb9f3116d041b36c8d272a3d3f5156ba0e042146d641db750  embree-3.5.2.x86_64.linux.tar.gz" | sha256sum -c - \
    && tar -xzf embree-3.5.2.x86_64.linux.tar.gz -C /opt \
    && rm -rf /opt/embree-3.5.2.x86_64.linux/bin \
    && rm -rf /opt/embree-3.5.2.x86_64.linux/doc \
    && rm embree-3.5.2.x86_64.linux.tar.gz

# mount points for filesystems on clusters
RUN mkdir -p /nfs \
    mkdir -p /oasis \
    mkdir -p /scratch \
    mkdir -p /work \
    mkdir -p /projects \
    mkdir -p /home1

RUN apt-get update && apt-get install -y --no-install-recommends \
  dkms \
  infiniband-diags \
  libibverbs-dev \
  ibacm \
  librdmacm-dev \
  mstflint \
  libibcm-dev \
  libibmad-dev \
  libibumad-dev \
  opensm \
  srptools \
  ibutils \
  ibverbs-utils \
  rdmacm-utils \
  perftest \
  numactl \
  libnuma-dev \
  libnl-3-200 \
  libnl-route-3-200 \
  libnl-route-3-dev \
  libnl-utils \
  && rm -rf /var/lib/apt/lists/*

# Intels OPA drivers don't support ubuntu. Copying these two files from Bridges seems to be the minimum
# needed to get the high performance interconnect working.
COPY hfi1.driver /etc/libibverbs.d/
COPY libhfi1verbs-rdmav2.so /usr/lib/

RUN curl -sSLO https://www.open-mpi.org/software/ompi/v2.1/downloads/openmpi-2.1.2.tar.bz2 \
   && echo "3cc5804984c5329bdf88effc44f2971ed244a29b256e0011b8deda02178dd635  openmpi-2.1.2.tar.bz2" | sha256sum -c - \
   && tar -xjf openmpi-2.1.2.tar.bz2 -C /root \
   && cd /root/openmpi-2.1.2 \
   && ./configure --prefix=/usr \
   && make all install \
   && rm -rf /root/openmpi-2.1.2 \
   && rm /openmpi-2.1.2.tar.bz2

RUN curl -sSLO http://mvapich.cse.ohio-state.edu/download/mvapich/osu-micro-benchmarks-5.4.1.tar.gz \
   && echo "e90cb683a01744377f77d420de401431242593d8376b25b120950266e140e83c  osu-micro-benchmarks-5.4.1.tar.gz" | sha256sum -c - \
   && tar -xzf osu-micro-benchmarks-5.4.1.tar.gz -C /root \
   && cd /root/osu-micro-benchmarks-5.4.1 \
   && ./configure --prefix=/opt/osu-micro-benchmarks CC=`which mpicc` CXX=`which mpicxx` \
   && cd mpi \
   && make install \
   && rm -rf /root/osu-micro-benchmarks-5.4.1 \
   && rm /osu-micro-benchmarks-5.4.1.tar.gz

RUN curl -sSLO https://bitbucket.org/mpi4py/mpi4py/downloads/mpi4py-3.0.0.tar.gz \
    && echo "b457b02d85bdd9a4775a097fac5234a20397b43e073f14d9e29b6cd78c68efd7  mpi4py-3.0.0.tar.gz" | sha256sum -c - \
    && tar -xz -f mpi4py-3.0.0.tar.gz -C /root \
    && cd /root/mpi4py-3.0.0 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/mpi4py-3.0.0 \
    && rm /mpi4py-3.0.0.tar.gz



RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v1.0.0.tar.gz \
    && echo "71599d85be07e6ed9afc3c85ec9a5ab5eafa8c8185fd4b306eb4ae43d5e127f2  freud-v1.0.0.tar.gz" | sha256sum -c - \
    && tar -xzf freud-v1.0.0.tar.gz -C . \
    && rm -f freud-v1.0.0/*.toml \
    && export CFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" CXXFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" \
    && python3 -m pip install --no-deps --ignore-installed ./freud-v1.0.0 \
    && rm -rf freud-v1.0.0 \
    && rm freud-v1.0.0.tar.gz \
    || exit 1


RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/fresnel/fresnel-v0.8.0.tar.gz \
    && echo "0bdb1f2249717b56f351492a06a0eb3bfe9f8ed0b4f490fdd73ef4cde922de31  fresnel-v0.8.0.tar.gz" | sha256sum -c - \
    && tar -xzf fresnel-v0.8.0.tar.gz -C . \
    && cd fresnel-v0.8.0 \
    && mkdir build \
    && cd build \
    && export CFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" CXXFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" \
    && cmake ../ -DENABLE_EMBREE=on -DENABLE_OPTIX=off -Dembree_DIR=/opt/embree-3.5.2.x86_64.linux -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && cd ../../ \
    && rm -rf fresnel-v0.8.0 \
    && rm fresnel-v0.8.0.tar.gz \
    || exit 1


RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.6.1.tar.gz \
    && echo "45edc981a5899ca7fb81205a3c1a3a07d58ea955f877fdd63e2a3e15d5ead41e  gsd-v1.6.1.tar.gz" | sha256sum -c - \
    && tar -xzf gsd-v1.6.1.tar.gz -C . \
    && cd gsd-v1.6.1 \
    && mkdir build \
    && cd build \
    && export CFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" CXXFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && cd ../../ \
    && rm -rf gsd-v1.6.1 \
    && rm gsd-v1.6.1.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/libgetar/libgetar-v0.7.0.tar.gz \
    && echo "2a33809981b7a99c856ca60a1a7b9b1a0b3978fd8315ab3ab07b7b279a7c55e7  libgetar-v0.7.0.tar.gz" | sha256sum -c - \
    && tar -xzf libgetar-v0.7.0.tar.gz -C . \
    && rm -f libgetar-v0.7.0/*.toml \
    && export CFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" CXXFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" \
    && python3 -m pip install --no-deps --ignore-installed ./libgetar-v0.7.0 \
    && rm -rf libgetar-v0.7.0 \
    && rm libgetar-v0.7.0.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/rowan/rowan-v1.2.0.tar.gz \
    && echo "68f27a6d7d1fd735a1cb0d465fd339ad137ea053fe7ccc56786464c33245dbeb  rowan-v1.2.0.tar.gz" | sha256sum -c - \
    && tar -xzf rowan-v1.2.0.tar.gz -C . \
    && export CFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" CXXFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" \
    && python3 -m pip install --no-deps --ignore-installed ./rowan-v1.2.0 \
    && rm -rf rowan-v1.2.0 \
    && rm rowan-v1.2.0.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/plato/plato-v1.4.0.tar.gz \
    && echo "fd5b764da5fdca9e704b22629b12c83fbf482db95fe7050e2b7b7661c8e57cdf  plato-v1.4.0.tar.gz" | sha256sum -c - \
    && tar -xzf plato-v1.4.0.tar.gz -C . \
    && export CFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" CXXFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" \
    && python3 -m pip install --no-deps --ignore-installed ./plato-v1.4.0 \
    && rm -rf plato-v1.4.0 \
    && rm plato-v1.4.0.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/pythia/pythia-v0.2.4.tar.gz \
    && echo "cebc1033759f518aa4f9c41d4660c7748b646f6f6117be9e4dcb9e53ef2f0251  pythia-v0.2.4.tar.gz" | sha256sum -c - \
    && tar -xzf pythia-v0.2.4.tar.gz -C . \
    && export CFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" CXXFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" \
    && python3 -m pip install --no-deps --ignore-installed ./pythia-v0.2.4 \
    && rm -rf pythia-v0.2.4 \
    && rm pythia-v0.2.4.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac/signac-v1.0.0.tar.gz \
    && echo "7eff681ec328a106ae9682697d2ed74565270a93410bab8583414fa756728ed0  signac-v1.0.0.tar.gz" | sha256sum -c - \
    && tar -xzf signac-v1.0.0.tar.gz -C . \
    && export CFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" CXXFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-v1.0.0 \
    && rm -rf signac-v1.0.0 \
    && rm signac-v1.0.0.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.6.4.tar.gz \
    && echo "c261204eef08c5e954179840cdb68795f2a464c213b58e67d7b502caada4d34c  signac-flow-v0.6.4.tar.gz" | sha256sum -c - \
    && tar -xzf signac-flow-v0.6.4.tar.gz -C . \
    && export CFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" CXXFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-flow-v0.6.4 \
    && chmod o+rX /usr/local/lib/**/dist-packages/flow/templates/* \
    && rm -rf signac-flow-v0.6.4 \
    && rm signac-flow-v0.6.4.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.5.1.tar.gz \
    && echo "07fcc83f7fb48373fe485bf7b8ac71cb79a2a6c918da3498dd64a37f2dc2c964  hoomd-v2.5.1.tar.gz" | sha256sum -c - \
    && tar -xzf hoomd-v2.5.1.tar.gz -C . \
    && cd hoomd-v2.5.1 \
    && mkdir build \
    && cd build \
    && export CFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" CXXFLAGS="-march=haswell -mmmx -msse -msse2 -msse3 -mssse3 -mcx16 -msahf -mmovbe -maes -mpclmul -mpopcnt -mabm -mfma -mbmi -mbmi2 -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mrdrnd -mf16c -mfsgsbase -mfxsr -mxsave -mxsaveopt --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell -fstack-protector-strong -Wformat -Wformat-security" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=on -DBUILD_JIT=on -DBUILD_TESTING=off -DENABLE_MPI_CUDA=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && cd ../../ \
    && rm -rf /root/hoomd-v2.5.1 \
    && rm hoomd-v2.5.1.tar.gz \
    || exit 1


RUN mkdir /hoomd-examples \
    && curl -sSL https://bitbucket.org/glotzer/hoomd-examples/get/master.tar.gz \
    | tar -xzC /hoomd-examples --strip-components=1

RUN mkdir /fresnel-examples \
    && curl -sSL https://bitbucket.org/glotzer/fresnel-examples/get/master.tar.gz \
    | tar -xzC /fresnel-examples --strip-components=1


# setup self test
RUN mkdir /test
COPY *.py job-*.sh /test/

# configure unprivileged user
RUN useradd --create-home --shell /bin/bash glotzerlab-software \
    && chown glotzerlab-software:glotzerlab-software -R /hoomd-examples \
    && chown glotzerlab-software:glotzerlab-software -R /fresnel-examples \
    && chown glotzerlab-software:glotzerlab-software -R /test \
    && chmod o+rX -R /test

USER glotzerlab-software:glotzerlab-software

LABEL maintainer="glotzerlab: http://glotzerlab.engin.umich.edu"