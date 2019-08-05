FROM nvidia/cuda:9.1-devel-ubuntu16.04

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
  python3-tables \
  python3-yaml \
  zlib1g-dev \
  ca-certificates \
  && rm -rf /var/lib/apt/lists/* \
  && pip3 install --no-cache-dir jupyter pillow pyhull deprecation

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

RUN curl -sSLO https://www.open-mpi.org/software/ompi/v3.0/downloads/openmpi-3.0.0.tar.bz2 \
   && echo "f699bff21db0125d8cccfe79518b77641cd83628725a1e1ed3e45633496a82d7  openmpi-3.0.0.tar.bz2" | sha256sum -c - \
   && tar -xjf openmpi-3.0.0.tar.bz2 -C /root \
   && cd /root/openmpi-3.0.0 \
   && ./configure --prefix=/usr \
   && make all install \
   && rm -rf /root/openmpi-3.0.0 \
   && rm /openmpi-3.0.0.tar.bz2

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



RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v1.2.1.tar.gz \
    && echo "4234ba0304742a8a2dd70df0663c23485c9cdd415789d34a434a76c116212d2e  freud-v1.2.1.tar.gz" | sha256sum -c - \
    && tar -xzf freud-v1.2.1.tar.gz -C . \
    && rm -f freud-v1.2.1/*.toml \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./freud-v1.2.1 \
    && rm -rf freud-v1.2.1 \
    && rm freud-v1.2.1.tar.gz \
    || exit 1


RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/fresnel/fresnel-v0.9.0.tar.gz \
    && echo "8f3d49bbb0c8410772f9d5a997b77b9546d512b8fba01ce5604dbf2b1499dd4e  fresnel-v0.9.0.tar.gz" | sha256sum -c - \
    && tar -xzf fresnel-v0.9.0.tar.gz -C . \
    && cd fresnel-v0.9.0 \
    && mkdir build \
    && cd build \
    && export CFLAGS="" CXXFLAGS="" \
    && cmake ../ -DENABLE_EMBREE=on -DENABLE_OPTIX=off -Dembree_DIR=/opt/embree-3.5.2.x86_64.linux -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && cd ../../ \
    && rm -rf fresnel-v0.9.0 \
    && rm fresnel-v0.9.0.tar.gz \
    || exit 1


RUN curl -sSLO https://glotzerlab.engin.umich.edu/downloads/garnett/garnett-v0.4.1.tar.gz \
    && echo "8e4860f676f92bc252d8ebc915c0ba6aeb35156f0105a685aebeb19ae54955b4  garnett-v0.4.1.tar.gz" | sha256sum -c - \
    && tar -xzf garnett-v0.4.1.tar.gz -C . \
    && rm -f garnett-v0.4.1/*.toml \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./garnett-v0.4.1 \
    && rm -rf garnett-v0.4.1 \
    && rm garnett-v0.4.1.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.8.0.tar.gz \
    && echo "f6a99e86198a2f01e9a33b6d5eafed5ed82fa7084e1661316ac06a660e2f809d  gsd-v1.8.0.tar.gz" | sha256sum -c - \
    && tar -xzf gsd-v1.8.0.tar.gz -C . \
    && cd gsd-v1.8.0 \
    && mkdir build \
    && cd build \
    && export CFLAGS="" CXXFLAGS="" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && cd ../../ \
    && rm -rf gsd-v1.8.0 \
    && rm gsd-v1.8.0.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/libgetar/libgetar-v1.0.1.tar.gz \
    && echo "0a438dc8336103158fc4dbb7ebcbc011279d7a8ae134824dda5946e6b9042039  libgetar-v1.0.1.tar.gz" | sha256sum -c - \
    && tar -xzf libgetar-v1.0.1.tar.gz -C . \
    && rm -f libgetar-v1.0.1/*.toml \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./libgetar-v1.0.1 \
    && rm -rf libgetar-v1.0.1 \
    && rm libgetar-v1.0.1.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/rowan/rowan-v1.2.1.tar.gz \
    && echo "c59ad2dded288e5626db19869ed2915852734520347f7e0afd9dd08171d4541b  rowan-v1.2.1.tar.gz" | sha256sum -c - \
    && tar -xzf rowan-v1.2.1.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./rowan-v1.2.1 \
    && rm -rf rowan-v1.2.1 \
    && rm rowan-v1.2.1.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/plato/plato-v1.6.0.tar.gz \
    && echo "d7282e2b7a8cd641e41a845f1a7075031b821440ab1ea9ad11a0dc991b86f91d  plato-v1.6.0.tar.gz" | sha256sum -c - \
    && tar -xzf plato-v1.6.0.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./plato-v1.6.0 \
    && rm -rf plato-v1.6.0 \
    && rm plato-v1.6.0.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/pythia/pythia-v0.2.5.tar.gz \
    && echo "5dfe1efeb7343fbfc7260dc6f05a8ee17908add288c67094d3740c7056627140  pythia-v0.2.5.tar.gz" | sha256sum -c - \
    && tar -xzf pythia-v0.2.5.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./pythia-v0.2.5 \
    && rm -rf pythia-v0.2.5 \
    && rm pythia-v0.2.5.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac/signac-v1.2.0.tar.gz \
    && echo "38591f2c0dcb77d28dfeb7906b2c25bfc3df39d67486ff819872ba69be4fa187  signac-v1.2.0.tar.gz" | sha256sum -c - \
    && tar -xzf signac-v1.2.0.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-v1.2.0 \
    && rm -rf signac-v1.2.0 \
    && rm signac-v1.2.0.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.7.1.tar.gz \
    && echo "970ea990d8c86143161670e7c260a66357323a55ee8a5b8d8d30fe00386a929c  signac-flow-v0.7.1.tar.gz" | sha256sum -c - \
    && tar -xzf signac-flow-v0.7.1.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-flow-v0.7.1 \
    && rm -rf signac-flow-v0.7.1 \
    && rm signac-flow-v0.7.1.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.6.0.tar.gz \
    && echo "f926b2d39cf58916794edbf4c619d0542a9b1e66b6c6a1b6a01b70f5617ec728  hoomd-v2.6.0.tar.gz" | sha256sum -c - \
    && tar -xzf hoomd-v2.6.0.tar.gz -C . \
    && cd hoomd-v2.6.0 \
    && mkdir build \
    && cd build \
    && export CFLAGS="" CXXFLAGS="" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=on -DBUILD_JIT=on -DBUILD_TESTING=off -DENABLE_MPI_CUDA=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && cd ../../ \
    && rm -rf /root/hoomd-v2.6.0 \
    && rm hoomd-v2.6.0.tar.gz \
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
    && chmod o+rX -R /test \
    && chmod o+rX `python3 -c "import site; print(site.getsitepackages()[0])"`/flow/templates/*

USER glotzerlab-software:glotzerlab-software

LABEL maintainer="glotzerlab: http://glotzerlab.engin.umich.edu"