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
ENV CPATH=/opt/embree-3.3.0.x86_64.linux/include:$CPATH \
    LIBRARY_PATH=/opt/embree-3.3.0.x86_64.linux/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=/opt/embree-3.3.0.x86_64.linux/lib:$LD_LIBRARY_PATH \
    EMBREE3_LINK=/opt/embree-3.3.0.x86_64.linux/lib

RUN curl -sSLO https://github.com/embree/embree/releases/download/v3.3.0/embree-3.3.0.x86_64.linux.tar.gz \
    && echo "c70e5cef5eeb88aa5c384121c8908287950d756c3eaac3f0bccea2d94c4fea3f  embree-3.3.0.x86_64.linux.tar.gz" | sha256sum -c - \
    && tar -xzf embree-3.3.0.x86_64.linux.tar.gz -C /opt \
    && rm -rf /opt/embree-3.3.0.x86_64.linux/bin \
    && rm -rf /opt/embree-3.3.0.x86_64.linux/doc \
    && rm embree-3.3.0.x86_64.linux.tar.gz

# mount points for filesystems on clusters
RUN mkdir -p /nfs \
    mkdir -p /oasis \
    mkdir -p /scratch \
    mkdir -p /work \
    mkdir -p /projects \
    mkdir -p /home1

ENV CC=/usr/bin/gcc-4.9
ENV CXX=/usr/bin/g++-4.9



 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/freud/freud-v0.11.4.tar.gz \
    && echo "9e54cb2f9ef2df7569ae04b5794d0372439b8667cd1ba32390496b5ddf3ad233  freud-v0.11.4.tar.gz" | sha256sum -c - \
    && tar -xzf freud-v0.11.4.tar.gz -C . \
    && rm -f freud-v0.11.4/*.toml \
    && export CFLAGS="-D_FORCE_INLINES" CXXFLAGS="-D_FORCE_INLINES" \
    && python3 -m pip install --no-deps --ignore-installed ./freud-v0.11.4 \
    && rm -rf freud-v0.11.4 \
    && rm freud-v0.11.4.tar.gz \
    || exit 1


 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/fresnel/fresnel-v0.6.0.tar.gz \
    && echo "de1b18f87b5bcdd96844c143d6a9cf560df873a9f1f7eae8d6ff2eac5a1d2467  fresnel-v0.6.0.tar.gz" | sha256sum -c - \
    && tar -xzf fresnel-v0.6.0.tar.gz -C . \
    && cd fresnel-v0.6.0 \
    && mkdir build \
    && cd build \
    && export CFLAGS="-D_FORCE_INLINES" CXXFLAGS="-D_FORCE_INLINES" \
    && cmake ../ -DENABLE_EMBREE=on -DENABLE_OPTIX=off -Dembree_DIR=/opt/embree-3.3.0.x86_64.linux -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j2 \
    && cd ../../ \
    && rm -rf fresnel-v0.6.0 \
    && rm fresnel-v0.6.0.tar.gz \
    || exit 1


 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/gsd/gsd-v1.5.5.tar.gz \
    && echo "465fbf207217e5d1223e6f3ab07a58ed5656b704f32730c27feaa0cfb6b6e70f  gsd-v1.5.5.tar.gz" | sha256sum -c - \
    && tar -xzf gsd-v1.5.5.tar.gz -C . \
    && cd gsd-v1.5.5 \
    && mkdir build \
    && cd build \
    && export CFLAGS="-D_FORCE_INLINES" CXXFLAGS="-D_FORCE_INLINES" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j2 \
    && cd ../../ \
    && rm -rf gsd-v1.5.5 \
    && rm gsd-v1.5.5.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/libgetar/libgetar-v0.7.0.tar.gz \
    && echo "2a33809981b7a99c856ca60a1a7b9b1a0b3978fd8315ab3ab07b7b279a7c55e7  libgetar-v0.7.0.tar.gz" | sha256sum -c - \
    && tar -xzf libgetar-v0.7.0.tar.gz -C . \
    && rm -f libgetar-v0.7.0/*.toml \
    && export CFLAGS="-D_FORCE_INLINES" CXXFLAGS="-D_FORCE_INLINES" \
    && python3 -m pip install --no-deps --ignore-installed ./libgetar-v0.7.0 \
    && rm -rf libgetar-v0.7.0 \
    && rm libgetar-v0.7.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/rowan/rowan-v1.1.6.tar.gz \
    && echo "14627245b95b88e3d4358e6d9df0501eec1bcb892c71ba5829904d4728ecb9f8  rowan-v1.1.6.tar.gz" | sha256sum -c - \
    && tar -xzf rowan-v1.1.6.tar.gz -C . \
    && export CFLAGS="-D_FORCE_INLINES" CXXFLAGS="-D_FORCE_INLINES" \
    && python3 -m pip install --no-deps --ignore-installed ./rowan-v1.1.6 \
    && rm -rf rowan-v1.1.6 \
    && rm rowan-v1.1.6.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/plato/plato-v1.3.0.tar.gz \
    && echo "ff079b6dead70fe2b1419277c8269d5c21dcbbd82c753aaa223e8614b5446d66  plato-v1.3.0.tar.gz" | sha256sum -c - \
    && tar -xzf plato-v1.3.0.tar.gz -C . \
    && export CFLAGS="-D_FORCE_INLINES" CXXFLAGS="-D_FORCE_INLINES" \
    && python3 -m pip install --no-deps --ignore-installed ./plato-v1.3.0 \
    && rm -rf plato-v1.3.0 \
    && rm plato-v1.3.0.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/pythia/pythia-v0.2.4.tar.gz \
    && echo "cebc1033759f518aa4f9c41d4660c7748b646f6f6117be9e4dcb9e53ef2f0251  pythia-v0.2.4.tar.gz" | sha256sum -c - \
    && tar -xzf pythia-v0.2.4.tar.gz -C . \
    && export CFLAGS="-D_FORCE_INLINES" CXXFLAGS="-D_FORCE_INLINES" \
    && python3 -m pip install --no-deps --ignore-installed ./pythia-v0.2.4 \
    && rm -rf pythia-v0.2.4 \
    && rm pythia-v0.2.4.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac/signac-v0.9.4.tar.gz \
    && echo "8a3c5b46d079decb9fa2d5d85628c2bd31057a44e945beba930d3b624dcb8437  signac-v0.9.4.tar.gz" | sha256sum -c - \
    && tar -xzf signac-v0.9.4.tar.gz -C . \
    && export CFLAGS="-D_FORCE_INLINES" CXXFLAGS="-D_FORCE_INLINES" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-v0.9.4 \
    && rm -rf signac-v0.9.4 \
    && rm signac-v0.9.4.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/signac-flow/signac-flow-v0.6.3.tar.gz \
    && echo "0a1ff4d052ea1e02079b60c0a5710df28e3fa8286649ccc030d032ec99901dba  signac-flow-v0.6.3.tar.gz" | sha256sum -c - \
    && tar -xzf signac-flow-v0.6.3.tar.gz -C . \
    && export CFLAGS="-D_FORCE_INLINES" CXXFLAGS="-D_FORCE_INLINES" \
    && python3 -m pip install --no-deps --ignore-installed ./signac-flow-v0.6.3 \
    && rm -rf signac-flow-v0.6.3 \
    && rm signac-flow-v0.6.3.tar.gz \
    || exit 1

 curl -sSLO https://glotzerlab.engin.umich.edu/Downloads/hoomd/hoomd-v2.4.1.tar.gz \
    && echo "0763c0f701f70439667256b67581b70052877330006cadd7b4eae7655fc913e9  hoomd-v2.4.1.tar.gz" | sha256sum -c - \
    && tar -xzf hoomd-v2.4.1.tar.gz -C . \
    && cd hoomd-v2.4.1 \
    && mkdir build \
    && cd build \
    && export CFLAGS="-D_FORCE_INLINES" CXXFLAGS="-D_FORCE_INLINES" \
    && cmake ../ -DPYTHON_EXECUTABLE="`which python3`" -DENABLE_CUDA=on -DENABLE_MPI=on -DENABLE_TBB=off -DBUILD_JIT=off -DBUILD_TESTING=off -DENABLE_MPI_CUDA=off -DCMAKE_INSTALL_PREFIX=`python3 -c "import site; print(site.getsitepackages()[0])"` \
    && make install -j2 \
    && cd ../../ \
    && rm -rf /root/hoomd-v2.4.1 \
    && rm hoomd-v2.4.1.tar.gz \
    || exit 1



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