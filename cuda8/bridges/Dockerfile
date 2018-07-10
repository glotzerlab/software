FROM nvidia/cuda:8.0-devel-ubuntu16.04

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
ENV CPATH=/opt/embree-2.17.1.x86_64.linux/include:$CPATH \
    LIBRARY_PATH=/opt/embree-2.17.1.x86_64.linux/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=/opt/embree-2.17.1.x86_64.linux/lib:$LD_LIBRARY_PATH \
    EMBREE_LINK=/opt/embree-2.17.1.x86_64.linux/lib

RUN curl -sSLO https://github.com/embree/embree/releases/download/v2.17.1/embree-2.17.1.x86_64.linux.tar.gz \
    && echo "e012149ab32abb0410d5b2cfec87cbc15f2c129e102fc6d5b4c84e4e484b68a1  embree-2.17.1.x86_64.linux.tar.gz" | sha256sum -c - \
    && tar -xzf embree-2.17.1.x86_64.linux.tar.gz -C /opt \
    && rm -rf /opt/embree-2.17.1.x86_64.linux/bin \
    && rm -rf /opt/embree-2.17.1.x86_64.linux/doc \
    && rm embree-2.17.1.x86_64.linux.tar.gz

# mount points for filesystems on clusters
RUN mkdir -p /nfs \
    mkdir -p /oasis \
    mkdir -p /scratch \
    mkdir -p /projects

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

RUN curl -sSLO https://www.open-mpi.org/software/ompi/v1.10/downloads/openmpi-1.10.4.tar.bz2 \
   && echo "fb3c0c4c77896185013b6091b306d29ba592eb40d8395533da5c8bc300d922db  openmpi-1.10.4.tar.bz2" | sha256sum -c - \
   && tar -xjf openmpi-1.10.4.tar.bz2 -C /root \
   && cd /root/openmpi-1.10.4 \
   && ./configure --prefix=/usr \
   && make all install \
   && rm -rf /root/openmpi-1.10.4 \
   && rm /openmpi-1.10.4.tar.bz2

RUN curl -sSLO http://mvapich.cse.ohio-state.edu/download/mvapich/osu-micro-benchmarks-5.4.1.tar.gz \
   && echo "e90cb683a01744377f77d420de401431242593d8376b25b120950266e140e83c  osu-micro-benchmarks-5.4.1.tar.gz" | sha256sum -c - \
   && tar -xzf osu-micro-benchmarks-5.4.1.tar.gz -C /root \
   && cd /root/osu-micro-benchmarks-5.4.1 \
   && ./configure --prefix=/opt/osu-micro-benchmarks CC=`which mpicc` CXX=`which mpicxx` \
   && cd mpi \
   && make install \
   && rm -rf /root/osu-micro-benchmarks-5.4.1 \
   && rm /osu-micro-benchmarks-5.4.1.tar.gz


# mpi4py
RUN curl -sSLO https://bitbucket.org/mpi4py/mpi4py/downloads/mpi4py-3.0.0.tar.gz \
    && echo "b457b02d85bdd9a4775a097fac5234a20397b43e073f14d9e29b6cd78c68efd7  mpi4py-3.0.0.tar.gz" | sha256sum -c - \
    && tar -xz -f mpi4py-3.0.0.tar.gz -C /root \
    && cd /root/mpi4py-3.0.0 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/mpi4py-3.0.0 \
    && rm /mpi4py-3.0.0.tar.gz


# set system specific cflags
ENV CFLAGS="-march=haswell -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -mno-sse4a -mcx16 -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mno-lwp -mfma -mno-fma4 -mno-xop -mbmi -mbmi2 -mno-tbm -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mno-rtm -mno-hle -mrdrnd -mf16c -mfsgsbase -mno-rdseed -mno-prfchw -mno-adx -mfxsr -mxsave -mxsaveopt -mno-avx512f -mno-avx512er -mno-avx512cd -mno-avx512pf -mno-prefetchwt1 -mno-clflushopt -mno-xsavec -mno-xsaves -mno-avx512dq -mno-avx512bw -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mno-clwb -mno-pcommit -mno-mwaitx --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell"
ENV CXXFLAGS="-march=haswell -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -mno-sse4a -mcx16 -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mno-lwp -mfma -mno-fma4 -mno-xop -mbmi -mbmi2 -mno-tbm -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mno-rtm -mno-hle -mrdrnd -mf16c -mfsgsbase -mno-rdseed -mno-prfchw -mno-adx -mfxsr -mxsave -mxsaveopt -mno-avx512f -mno-avx512er -mno-avx512cd -mno-avx512pf -mno-prefetchwt1 -mno-clflushopt -mno-xsavec -mno-xsaves -mno-avx512dq -mno-avx512bw -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mno-clwb -mno-pcommit -mno-mwaitx --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell"

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.3.3.tar.gz \
    && echo "af130549334c346472bd4c8fed087ddda5289f9a65dfd8d22f64c348f2fec092  hoomd-v2.3.3.tar.gz" | sha256sum -c - \
    && tar -xzf hoomd-v2.3.3.tar.gz -C /root \
    && cd /root/hoomd-v2.3.3 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=on -DBUILD_JIT=on -DBUILD_TESTING=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/hoomd-v2.3.3 \
    && rm /hoomd-v2.3.3.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.8.2.tar.gz \
    && echo "e4c2c3dbddb70f42fb526375186b882ce35073d75ca494cabbec478aa523ab48  freud-v0.8.2.tar.gz" | sha256sum -c - \
    && tar -xzf freud-v0.8.2.tar.gz -C /root \
    && cd /root/freud-v0.8.2 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/freud-v0.8.2 \
    && rm /freud-v0.8.2.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/fresnel/fresnel-v0.5.0.tar.gz \
    && echo "6d73e33f335aa39bd12839f9a4aa863805a1f58da85e3abe8df74aeb3b010550  fresnel-v0.5.0.tar.gz" | sha256sum -c - \
    && tar -xzf fresnel-v0.5.0.tar.gz -C /root \
    && cd /root/fresnel-v0.5.0 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_TBB=on -DENABLE_EMBREE=on -DENABLE_CUDA=off -DENABLE_OPTIX=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/fresnel-v0.5.0 \
    && rm /fresnel-v0.5.0.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.5.3.tar.gz \
    && echo "10b6d37b2dadb9dc3543f4975e3722da3f3fd790df44e887b2a0306c045cf76d  gsd-v1.5.3.tar.gz" | sha256sum -c - \
    && tar -xzf gsd-v1.5.3.tar.gz -C /root \
    && cd /root/gsd-v1.5.3 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/gsd-v1.5.3 \
    && rm /gsd-v1.5.3.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/libgetar/libgetar-v0.5.4.tar.gz \
    && echo "781d972b32e4d02bf2c396bad19a585f682329df0d1d630c0b34405e70dd9c70  libgetar-v0.5.4.tar.gz" | sha256sum -c - \
    && tar -xzf libgetar-v0.5.4.tar.gz -C /root \
    && cd /root/libgetar-v0.5.4 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/libgetar-v0.5.4 \
    && rm /libgetar-v0.5.4.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/rowan/rowan-v0.6.1.tar.gz \
    && echo "31b10e78013219a178336b9fd85c01ba3f0dbee34e676b8240d88bb796d48b8e  rowan-v0.6.1.tar.gz" | sha256sum -c - \
    && tar -xzf rowan-v0.6.1.tar.gz -C /root \
    && cd /root/rowan-v0.6.1 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/rowan-v0.6.1 \
    && rm /rowan-v0.6.1.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/plato/plato-v1.1.0.tar.gz \
    && echo "ad1b213f28990e34677bcd6449f17852420a0c6ed8b807ec842b6a0b0433a8ad  plato-v1.1.0.tar.gz" | sha256sum -c - \
    && tar -xzf plato-v1.1.0.tar.gz -C /root \
    && cd /root/plato-v1.1.0 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/plato-v1.1.0 \
    && rm /plato-v1.1.0.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/pythia/pythia-v0.2.2.tar.gz \
    && echo "38992fd2f10368681b3151b2cba999e9fa413f811882d0900c3e0ee5cb25e400  pythia-v0.2.2.tar.gz" | sha256sum -c - \
    && tar -xzf pythia-v0.2.2.tar.gz -C /root \
    && cd /root/pythia-v0.2.2 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/pythia-v0.2.2 \
    && rm /pythia-v0.2.2.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac/signac-v0.9.3.tar.gz \
    && echo "b54f977d347180d6f7a737d84a63bcc1140d7e6f4fe681f8b8315db6fe32d7ab  signac-v0.9.3.tar.gz" | sha256sum -c - \
    && tar -xzf signac-v0.9.3.tar.gz -C /root \
    && cd /root/signac-v0.9.3 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/signac-v0.9.3 \
    && rm /signac-v0.9.3.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.6.1.tar.gz \
    && echo "417e31a922bf236758ffc2a715c0beca2888cc9406342c311329c79636e130ac  signac-flow-v0.6.1.tar.gz" | sha256sum -c - \
    && tar -xzf signac-flow-v0.6.1.tar.gz -C /root \
    && cd /root/signac-flow-v0.6.1 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/signac-flow-v0.6.1 \
    && rm /signac-flow-v0.6.1.tar.gz

RUN mkdir /hoomd-examples \
    && curl -sSL https://bitbucket.org/glotzer/hoomd-examples/get/master.tar.gz \
    | tar -xzC /hoomd-examples --strip-components=1

RUN mkdir /fresnel-examples \
    && curl -sSL https://bitbucket.org/glotzer/fresnel-examples/get/master.tar.gz \
    | tar -xzC /fresnel-examples --strip-components=1

# configure unprivileged user
RUN useradd --create-home --shell /bin/bash glotzerlab-software \
    && chown glotzerlab-software:glotzerlab-software -R /hoomd-examples \
    && chown glotzerlab-software:glotzerlab-software -R /fresnel-examples

USER glotzerlab-software:glotzerlab-software

# unset CFLAGS to work around stampede2 bug
ENV CFLAGS=""
ENV CXXFLAGS=""