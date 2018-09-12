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
ENV CPATH=/opt/embree-3.2.0.x86_64.linux/include:$CPATH \
    LIBRARY_PATH=/opt/embree-3.2.0.x86_64.linux/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=/opt/embree-3.2.0.x86_64.linux/lib:$LD_LIBRARY_PATH \
    EMBREE3_LINK=/opt/embree-3.2.0.x86_64.linux/lib

RUN curl -sSLO https://github.com/embree/embree/releases/download/v3.2.0/embree-3.2.0.x86_64.linux.tar.gz \
    && echo "7671cc37c4dc4e3da00b2b299b906b35816f058efea92701e7b89574b15e652d  embree-3.2.0.x86_64.linux.tar.gz" | sha256sum -c - \
    && tar -xzf embree-3.2.0.x86_64.linux.tar.gz -C /opt \
    && rm -rf /opt/embree-3.2.0.x86_64.linux/bin \
    && rm -rf /opt/embree-3.2.0.x86_64.linux/doc \
    && rm embree-3.2.0.x86_64.linux.tar.gz

# mount points for filesystems on clusters
RUN mkdir -p /nfs \
    mkdir -p /oasis \
    mkdir -p /scratch \
    mkdir -p /projects



# set system specific cflags
ENV CFLAGS=""
ENV CXXFLAGS=""

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.3.4.tar.gz \
    && echo "72bea429483528d38e8c8da77cc4b0fa6df6dcfd8846bbe9d7975a007c749525  hoomd-v2.3.4.tar.gz" | sha256sum -c - \
    && tar -xzf hoomd-v2.3.4.tar.gz -C /root \
    && cd /root/hoomd-v2.3.4 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_CUDA=on -DENABLE_MPI=off -DENABLE_TBB=on -DBUILD_JIT=on -DBUILD_TESTING=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/hoomd-v2.3.4 \
    && rm /hoomd-v2.3.4.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.10.0.tar.gz \
    && echo "f0d00cf5d958b0e3b819ab09ba0433f2fb29b0cdac30879222d49cad7e460e1f  freud-v0.10.0.tar.gz" | sha256sum -c - \
    && tar -xzf freud-v0.10.0.tar.gz -C /root \
    && cd /root/freud-v0.10.0 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/freud-v0.10.0 \
    && rm /freud-v0.10.0.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/fresnel/fresnel-v0.6.0.tar.gz \
    && echo "de1b18f87b5bcdd96844c143d6a9cf560df873a9f1f7eae8d6ff2eac5a1d2467  fresnel-v0.6.0.tar.gz" | sha256sum -c - \
    && tar -xzf fresnel-v0.6.0.tar.gz -C /root \
    && cd /root/fresnel-v0.6.0 \
    && mkdir build \
    && cd build \
    && cmake ../ -DENABLE_EMBREE=on -DENABLE_OPTIX=off -Dembree_DIR=/opt/embree-3.2.0.x86_64.linux -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && rm -rf /root/fresnel-v0.6.0 \
    && rm /fresnel-v0.6.0.tar.gz

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

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/libgetar/libgetar-v0.6.1.tar.gz \
    && echo "3e7e0124ba6b7c831e789e13d75313a4700fbea9b0d04ebd5c1afc87b732aa24  libgetar-v0.6.1.tar.gz" | sha256sum -c - \
    && tar -xzf libgetar-v0.6.1.tar.gz -C /root \
    && cd /root/libgetar-v0.6.1 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/libgetar-v0.6.1 \
    && rm /libgetar-v0.6.1.tar.gz

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/rowan/rowan-v1.1.0.tar.gz \
    && echo "43a7a29a95409acb458184647081c0e6e178943018db58f993e771b9d48602c7  rowan-v1.1.0.tar.gz" | sha256sum -c - \
    && tar -xzf rowan-v1.1.0.tar.gz -C /root \
    && cd /root/rowan-v1.1.0 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/rowan-v1.1.0 \
    && rm /rowan-v1.1.0.tar.gz

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

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.6.3.tar.gz \
    && echo "0a1ff4d052ea1e02079b60c0a5710df28e3fa8286649ccc030d032ec99901dba  signac-flow-v0.6.3.tar.gz" | sha256sum -c - \
    && tar -xzf signac-flow-v0.6.3.tar.gz -C /root \
    && cd /root/signac-flow-v0.6.3 \
    && python3 -m pip install --no-deps --ignore-installed . \
    && rm -rf /root/signac-flow-v0.6.3 \
    && rm /signac-flow-v0.6.3.tar.gz

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