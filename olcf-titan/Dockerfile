FROM olcf/titan:ubuntu-16.04_2018-01-18

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

ENV CC=/usr/bin/gcc-4.9
ENV CXX=/usr/bin/g++-4.9


# mpi4py
RUN curl -sSL https://bitbucket.org/mpi4py/mpi4py/downloads/mpi4py-3.0.0.tar.gz \
    | tar -xzC /root \
    && cd /root/mpi4py-3.0.0 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/mpi4py-3.0.0


# set system specific cflags
ENV CFLAGS="-D_FORCE_INLINES"
ENV CXXFLAGS="-D_FORCE_INLINES"

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.3.2.tar.gz \
    | tar -xzC /root \
    && cd /root/hoomd-v2.3.2 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=on -DBUILD_JIT=on -DBUILD_TESTING=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j2 \
    && rm -rf /root/hoomd-v2.3.2

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.8.2.tar.gz \
    | tar -xzC /root \
    && cd /root/freud-v0.8.2 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j2 \
    && rm -rf /root/freud-v0.8.2

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/fresnel/fresnel-v0.5.0.tar.gz \
    | tar -xzC /root \
    && cd /root/fresnel-v0.5.0 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_TBB=on -DENABLE_EMBREE=on -DENABLE_CUDA=off -DENABLE_OPTIX=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j2 \
    && rm -rf /root/fresnel-v0.5.0

RUN curl -sSL https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.5.3.tar.gz \
    | tar -xzC /root \
    && cd /root/gsd-v1.5.3 \
    && mkdir build \
    && cd build \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j2 \
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