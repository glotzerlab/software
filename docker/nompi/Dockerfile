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
ENV CPATH=/opt/embree-3.2.1.x86_64.linux/include:$CPATH \
    LIBRARY_PATH=/opt/embree-3.2.1.x86_64.linux/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=/opt/embree-3.2.1.x86_64.linux/lib:$LD_LIBRARY_PATH \
    EMBREE3_LINK=/opt/embree-3.2.1.x86_64.linux/lib

RUN curl -sSLO https://github.com/embree/embree/releases/download/v3.2.1/embree-3.2.1.x86_64.linux.tar.gz \
    && echo "4bc1801d7a358dfd71e1fb6d46c9401397923980c11e7801f26d5b3f1aed4506  embree-3.2.1.x86_64.linux.tar.gz" | sha256sum -c - \
    && tar -xzf embree-3.2.1.x86_64.linux.tar.gz -C /opt \
    && rm -rf /opt/embree-3.2.1.x86_64.linux/bin \
    && rm -rf /opt/embree-3.2.1.x86_64.linux/doc \
    && rm embree-3.2.1.x86_64.linux.tar.gz

# mount points for filesystems on clusters
RUN mkdir -p /nfs \
    mkdir -p /oasis \
    mkdir -p /scratch \
    mkdir -p /work \
    mkdir -p /projects \
    mkdir -p /home1



RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.11.3.tar.gz \
    && echo "fc803bd20a43b998cc660011ac408c51750427bebe5e26131aef9f9446fe53ec  freud-v0.11.3.tar.gz" | sha256sum -c - \
    && tar -xzf freud-v0.11.3.tar.gz -C . \
    && rm -f freud-v0.11.3/*.toml \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./freud-v0.11.3 \
    && rm -rf freud-v0.11.3 \
    && rm freud-v0.11.3.tar.gz \
    || exit 1


RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/fresnel/fresnel-v0.6.0.tar.gz \
    && echo "de1b18f87b5bcdd96844c143d6a9cf560df873a9f1f7eae8d6ff2eac5a1d2467  fresnel-v0.6.0.tar.gz" | sha256sum -c - \
    && tar -xzf fresnel-v0.6.0.tar.gz -C . \
    && cd fresnel-v0.6.0 \
    && mkdir build \
    && cd build \
    && export CFLAGS="" CXXFLAGS="" \
    && cmake ../ -DENABLE_EMBREE=on -DENABLE_OPTIX=off -Dembree_DIR=/opt/embree-3.2.1.x86_64.linux -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && cd ../../ \
    && rm -rf fresnel-v0.6.0 \
    && rm fresnel-v0.6.0.tar.gz \
    || exit 1


RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.5.4.tar.gz \
    && echo "09b09f1316c809dae96b1a02972673ef928eb549fcc1cae484265590a5b4acff  gsd-v1.5.4.tar.gz" | sha256sum -c - \
    && tar -xzf gsd-v1.5.4.tar.gz -C . \
    && cd gsd-v1.5.4 \
    && mkdir build \
    && cd build \
    && export CFLAGS="" CXXFLAGS="" \
    && cmake ../ -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && cd ../../ \
    && rm -rf gsd-v1.5.4 \
    && rm gsd-v1.5.4.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/libgetar/libgetar-v0.7.0.tar.gz \
    && echo "2a33809981b7a99c856ca60a1a7b9b1a0b3978fd8315ab3ab07b7b279a7c55e7  libgetar-v0.7.0.tar.gz" | sha256sum -c - \
    && tar -xzf libgetar-v0.7.0.tar.gz -C . \
    && rm -f libgetar-v0.7.0/*.toml \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./libgetar-v0.7.0 \
    && rm -rf libgetar-v0.7.0 \
    && rm libgetar-v0.7.0.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/rowan/rowan-v1.1.6.tar.gz \
    && echo "14627245b95b88e3d4358e6d9df0501eec1bcb892c71ba5829904d4728ecb9f8  rowan-v1.1.6.tar.gz" | sha256sum -c - \
    && tar -xzf rowan-v1.1.6.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./rowan-v1.1.6 \
    && rm -rf rowan-v1.1.6 \
    && rm rowan-v1.1.6.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/plato/plato-v1.2.0.tar.gz \
    && echo "fdd574a5ed6956bb68430de13991938d4765697736c857822c8c1addf5edd07d  plato-v1.2.0.tar.gz" | sha256sum -c - \
    && tar -xzf plato-v1.2.0.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./plato-v1.2.0 \
    && rm -rf plato-v1.2.0 \
    && rm plato-v1.2.0.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/pythia/pythia-v0.2.3.tar.gz \
    && echo "6fa74e608024d8126657d788016ec3a4112a7c17b8deda86e51a2905c47f5ed5  pythia-v0.2.3.tar.gz" | sha256sum -c - \
    && tar -xzf pythia-v0.2.3.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./pythia-v0.2.3 \
    && rm -rf pythia-v0.2.3 \
    && rm pythia-v0.2.3.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac/signac-v0.9.4.tar.gz \
    && echo "8a3c5b46d079decb9fa2d5d85628c2bd31057a44e945beba930d3b624dcb8437  signac-v0.9.4.tar.gz" | sha256sum -c - \
    && tar -xzf signac-v0.9.4.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-v0.9.4 \
    && rm -rf signac-v0.9.4 \
    && rm signac-v0.9.4.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.6.3.tar.gz \
    && echo "0a1ff4d052ea1e02079b60c0a5710df28e3fa8286649ccc030d032ec99901dba  signac-flow-v0.6.3.tar.gz" | sha256sum -c - \
    && tar -xzf signac-flow-v0.6.3.tar.gz -C . \
    && export CFLAGS="" CXXFLAGS="" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-flow-v0.6.3 \
    && rm -rf signac-flow-v0.6.3 \
    && rm signac-flow-v0.6.3.tar.gz \
    || exit 1

RUN curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.4.0.tar.gz \
    && echo "052fffd0ebcc43a86fa530ff54054ae183dcd5c404957e41f7d83f633e39569a  hoomd-v2.4.0.tar.gz" | sha256sum -c - \
    && tar -xzf hoomd-v2.4.0.tar.gz -C . \
    && cd hoomd-v2.4.0 \
    && mkdir build \
    && cd build \
    && export CFLAGS="" CXXFLAGS="" \
    && cmake ../ -DENABLE_CUDA=on -DENABLE_MPI=off -DENABLE_TBB=on -DBUILD_JIT=on -DBUILD_TESTING=off -DENABLE_MPI_CUDA=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j10 \
    && cd ../../ \
    && rm -rf /root/hoomd-v2.4.0 \
    && rm hoomd-v2.4.0.tar.gz \
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