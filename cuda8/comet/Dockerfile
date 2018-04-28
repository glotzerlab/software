FROM nvidia/cuda:8.0-devel-ubuntu16.04

RUN apt-get update && apt-get install -y --no-install-recommends \
  clang-5.0 \
  cmake \
  curl \
  cython3 \
  git \
  ipython3 \
  libboost-dev \
  libedit-dev \
  libtbb-dev \
  libsqlite3-dev \
  llvm-5.0-dev \
  python3 \
  python3-dev \
  python3-matplotlib \
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

# put clang on the path
ENV PATH=$PATH:/usr/lib/llvm-5.0/bin

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

# packages needed to support IB on Comet
# https://github.com/mkandes/naked-singularity/blob/master/definition-files/us/ucsd/sdsc/comet/ubuntu/ubuntu-openmpi.def
RUN apt-get update && apt-get install -y --no-install-recommends \
  dkms \
  infiniband-diags \
  libibverbs-dev \
  ibacm \
  librdmacm-dev \
  libmlx4-dev \
  libmlx5-dev \
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

RUN curl -sSL https://www.open-mpi.org/software/ompi/v1.8/downloads/openmpi-1.8.4.tar.bz2 \
   | tar -xjC /root \
   && cd /root/openmpi-1.8.4 \
   && ./configure --prefix=/usr \
   && make all install \
   && rm -rf /root/openmpi-1.8.4

RUN curl -sSL http://mvapich.cse.ohio-state.edu/download/mvapich/osu-micro-benchmarks-5.4.1.tar.gz \
   | tar -xzC /root \
   && cd /root/osu-micro-benchmarks-5.4.1 \
   && ./configure --prefix=/opt/osu-micro-benchmarks CC=`which mpicc` CXX=`which mpicxx` \
   && cd mpi \
   && make install \
   && rm -rf /root/osu-micro-benchmarks-5.4.1
# LD_LIBRARY_PATH is a workaround for hoomd v2.3.0, it should not be needed in 2.3.1+
ENV LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib/python3.5/dist-packages/hoomd
RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.3.0.tar.gz \
    | tar -xzC /root \
    && cd /root/hoomd-v2.3.0 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=on -DBUILD_JIT=on -DBUILD_TESTING=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/hoomd-v2.3.0

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.8.0.tar.gz \
    | tar -xzC /root \
    && cd /root/freud-v0.8.0 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/freud-v0.8.0

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

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.5.2.tar.gz \
    | tar -xzC /root \
    && cd /root/gsd-v1.5.2 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/gsd-v1.5.2