FROM nvidia/cuda:8.0-devel-ubuntu16.04

RUN apt-get update && apt-get install -y --no-install-recommends \
  clang-5.0 \
  cmake \
  curl \
  cython3 \
  g++-4.9 \
  gcc-4.9 \
  git \
  ipython3 \
  libboost-dev \
  libedit-dev \
  libtbb-dev \
  libsqlite3-dev \
  python3 \
  python3-dev \
  python3-nose \
  python3-numpy \
  python3-pil \
  python3-pip \
  python3-pytest \
  python3-setuptools \
  python3-sphinx \
  python3-sphinx-rtd-theme \
  zlib1g-dev \
  ca-certificates \
  && rm -rf /var/lib/apt/lists/*

# embree
ENV CPATH=/opt/embree-2.17.1.x86_64.linux/include:$CPATH \
    LIBRARY_PATH=/opt/embree-2.17.1.x86_64.linux/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=/opt/embree-2.17.1.x86_64.linux/lib:$LD_LIBRARY_PATH \
    EMBREE_LINK=/opt/embree-2.17.1.x86_64.linux/lib

RUN curl -sSL https://github.com/embree/embree/releases/download/v2.17.1/embree-2.17.1.x86_64.linux.tar.gz \
    | tar -xzC /opt \
    && rm -rf /opt/embree-2.17.1.x86_64.linux/include/bin

# mount points for filesystems on clusters
RUN mkdir -p /nfs \
    mkdir -p /oasis \
    mkdir -p /scratch \
    mkdir -p /projects

# IB drivers for MPI (https://community.mellanox.com/docs/DOC-2431)
# TODO: install MLNX_OFED
RUN apt-get update && apt-get install -y --no-install-recommends \
  libhwloc-plugins \
  libhwloc5 \
  infiniband-diags \
  libibverbs* \
  ibacm \
  librdmacm* \
  libmlx4* \
  libmlx5* \
  libpsm-infinipath1 \
  mstflint \
  libibcm.* \
  libibmad.* \
  libibumad* \
  opensm \
  srptools \
  libmlx4-dev \
  rdmacm-utils \
  ibverbs-utils \
  perftest \
  vlan \
  ibutils \
  libnl-3-200 \
  libnl-route-3-200 \
  libnl-route-3-dev \
  libnl-utils \
  libnuma-dev \
  libpciaccess0 \
  byacc \
  flex \
  && rm -rf /var/lib/apt/lists/*


RUN curl -sSL https://www.open-mpi.org/software/ompi/v3.0/downloads/openmpi-3.0.0.tar.bz2 \
   | tar -xjC /root \
   && cd /root/openmpi-3.0.0 \
   && ./configure --prefix=/usr \
                  --with-verbs \
                  --disable-dlopen --enable-shared \
   && make install -j8 \
   && rm -rf /root/openmpi-3.0.0

RUN curl -sSL http://mvapich.cse.ohio-state.edu/download/mvapich/osu-micro-benchmarks-5.4.1.tar.gz \
   | tar -xzC /root \
   && cd /root/osu-micro-benchmarks-5.4.1 \
   && ./configure --prefix=/opt/osu-micro-benchmarks CC=`which mpicc` CXX=`which mpicxx` \
   && cd mpi \
   && make install -j8 \
   && rm -rf /root/osu-micro-benchmarks-5.4.1

ENV CC=/usr/bin/gcc
ENV CXX=/usr/bin/g++

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.2.4.tar.gz \
    | tar -xzC /root \
    && cd /root/hoomd-v2.2.4 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_CUDA=on -DENABLE_MPI=on -DBUILD_TESTING=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/hoomd-v2.2.4

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.7.0.tar.gz \
    | tar -xzC /root \
    && cd /root/freud-v0.7.0 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/freud-v0.7.0

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/fresnel/fresnel-v0.5.0.tar.gz \
    | tar -xzC /root \
    && cd /root/fresnel-v0.5.0 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_TBB=on -DENABLE_EMBREE=on -DENABLE_CUDA=off -DENABLE_OPTIX=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/fresnel-v0.5.0

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/signac/signac-v0.9.2.tar.gz \
    | tar -xzC /root \
    && cd /root/signac-v0.9.2 \
    && python3 setup.py install \
    && rm -rf /root/signac-v0.9.2

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.5.6.tar.gz \
    | tar -xzC /root \
    && cd /root/signac-flow-v0.5.6 \
    && python3 setup.py install \
    && rm -rf /root/signac-flow-v0.5.6

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.5.1.tar.gz \
    | tar -xzC /root \
    && cd /root/gsd-v1.5.1 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/gsd-v1.5.1