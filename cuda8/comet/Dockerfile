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


# mpi4py
RUN curl -sSL https://bitbucket.org/mpi4py/mpi4py/downloads/mpi4py-3.0.0.tar.gz \
    | tar -xzC /root \
    && cd /root/mpi4py-3.0.0 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/mpi4py-3.0.0


# set system specific cflags
ENV CFLAGS="-march=haswell -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -mno-sse4a -mcx16 -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mno-lwp -mfma -mno-fma4 -mno-xop -mbmi -mbmi2 -mno-tbm -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mno-rtm -mno-hle -mrdrnd -mf16c -mfsgsbase -mno-rdseed -mno-prfchw -mno-adx -mfxsr -mxsave -mxsaveopt -mno-avx512f -mno-avx512er -mno-avx512cd -mno-avx512pf -mno-prefetchwt1 -mno-clflushopt -mno-xsavec -mno-xsaves -mno-avx512dq -mno-avx512bw -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mno-clwb -mno-pcommit -mno-mwaitx --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell"
ENV CXXFLAGS="-march=haswell -mmmx -mno-3dnow -msse -msse2 -msse3 -mssse3 -mno-sse4a -mcx16 -msahf -mmovbe -maes -mno-sha -mpclmul -mpopcnt -mabm -mno-lwp -mfma -mno-fma4 -mno-xop -mbmi -mbmi2 -mno-tbm -mavx -mavx2 -msse4.2 -msse4.1 -mlzcnt -mno-rtm -mno-hle -mrdrnd -mf16c -mfsgsbase -mno-rdseed -mno-prfchw -mno-adx -mfxsr -mxsave -mxsaveopt -mno-avx512f -mno-avx512er -mno-avx512cd -mno-avx512pf -mno-prefetchwt1 -mno-clflushopt -mno-xsavec -mno-xsaves -mno-avx512dq -mno-avx512bw -mno-avx512vl -mno-avx512ifma -mno-avx512vbmi -mno-clwb -mno-pcommit -mno-mwaitx --param l1-cache-size=32 --param l1-cache-line-size=64 --param l2-cache-size=35840 -mtune=haswell"

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.3.2.tar.gz \
    | tar -xzC /root \
    && cd /root/hoomd-v2.3.2 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=on -DBUILD_JIT=on -DBUILD_TESTING=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/hoomd-v2.3.2

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.8.2.tar.gz \
    | tar -xzC /root \
    && cd /root/freud-v0.8.2 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/freud-v0.8.2

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/fresnel/fresnel-v0.5.0.tar.gz \
    | tar -xzC /root \
    && cd /root/fresnel-v0.5.0 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_TBB=on -DENABLE_EMBREE=on -DENABLE_CUDA=off -DENABLE_OPTIX=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/fresnel-v0.5.0

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.5.3.tar.gz \
    | tar -xzC /root \
    && cd /root/gsd-v1.5.3 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/gsd-v1.5.3

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/libgetar/libgetar-v0.5.4.tar.gz \
    | tar -xzC /root \
    && cd /root/libgetar-v0.5.4 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/libgetar-v0.5.4

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/rowan/rowan-v0.6.1.tar.gz \
    | tar -xzC /root \
    && cd /root/rowan-v0.6.1 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/rowan-v0.6.1

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/plato/plato-v1.1.0.tar.gz \
    | tar -xzC /root \
    && cd /root/plato-v1.1.0 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/plato-v1.1.0

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/pythia/pythia-v0.2.2.tar.gz \
    | tar -xzC /root \
    && cd /root/pythia-v0.2.2 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/pythia-v0.2.2

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/signac/signac-v0.9.3.tar.gz \
    | tar -xzC /root \
    && cd /root/signac-v0.9.3 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/signac-v0.9.3

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.6.0.tar.gz \
    | tar -xzC /root \
    && cd /root/signac-flow-v0.6.0 \
    && python3 -m pip install --no-deps --ignore-installed \
    && rm -rf /root/signac-flow-v0.6.0

RUN mkdir /hoomd-examples \
    && curl -sSL https://bitbucket.org/glotzer/hoomd-examples/get/master.tar.gz \
    | tar -xzC /hoomd-examples --strip-components=1

RUN mkdir /fresnel-examples \
    && curl -sSL https://bitbucket.org/glotzer/fresnel-examples/get/master.tar.gz \
    | tar -xzC /fresnel-examples --strip-components=1

# configure unprivileged user
RUN useradd --create-home --shell /bin/bash glotzerlab-software \
    && chown glotzerlab-software:glotzerlab-software -R /hoomd-examples
USER glotzerlab-software:glotzerlab-software