FROM olcf/titan:ubuntu-16.04_2018-01-18

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

ENV CC=/usr/bin/gcc-4.9
ENV CXX=/usr/bin/g++-4.9
ENV CFLAGS=-D_FORCE_INLINES
ENV CXXFLAGS=-D_FORCE_INLINES

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.2.4.tar.gz \
    | tar -xzC /root \
    && cd /root/hoomd-v2.2.4 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_CUDA=on -DENABLE_MPI=on -DBUILD_TESTING=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j2 \
    && rm -rf /root/hoomd-v2.2.4

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.7.0.tar.gz \
    | tar -xzC /root \
    && cd /root/freud-v0.7.0 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j2 \
    && rm -rf /root/freud-v0.7.0

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/fresnel/fresnel-v0.5.0.tar.gz \
    | tar -xzC /root \
    && cd /root/fresnel-v0.5.0 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_TBB=on -DENABLE_EMBREE=on -DENABLE_CUDA=off -DENABLE_OPTIX=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j2 \
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
    && make install -j2 \
    && rm -rf /root/gsd-v1.5.1