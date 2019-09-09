FROM nvidia/cuda:9.2-devel-ubuntu16.04

ENV DEBIAN_FRONTEND=noninteractive




RUN apt-get update && apt-get install -y --no-install-recommends \
  clang-5.0 \
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

# install modern cmake
RUN curl -SL https://github.com/Kitware/CMake/releases/download/v3.15.3/cmake-3.15.3.tar.gz | tar -xzC /root && \
    cd /root/cmake-3.15.3 && \
    ./bootstrap && \
    make && \
    make install && \
    cd / && rm -rf /root/cmake-*

# put clang on the path
ENV PATH=$PATH:/usr/lib/llvm-5.0/bin


# prevent python from loading packages from outside the container
# default empty pythonpath
ENV PYTHONPATH=/ignore/pythonpath
# disable user site directories (https://docs.python.org/3/library/site.html#module-site)
RUN sed -i -e 's/ENABLE_USER_SITE = None/ENABLE_USER_SITE = False/g' `python3 -c 'import site; print(site.__file__)'`

# embree
ENV CPATH=/opt/embree-3.6.1.x86_64.linux/include:$CPATH \
    LIBRARY_PATH=/opt/embree-3.6.1.x86_64.linux/lib:$LIBRARY_PATH \
    LD_LIBRARY_PATH=/opt/embree-3.6.1.x86_64.linux/lib:$LD_LIBRARY_PATH \
    EMBREE3_LINK=/opt/embree-3.6.1.x86_64.linux/lib

RUN curl -sSLO https://github.com/embree/embree/releases/download/v3.6.1/embree-3.6.1.x86_64.linux.tar.gz \
    && echo "76e9c619e11c2baace2935b14f1d6ee8ff085fd12c72b7d62d6fcb9a4ffaca3e  embree-3.6.1.x86_64.linux.tar.gz" | sha256sum -c - \
    && tar -xzf embree-3.6.1.x86_64.linux.tar.gz -C /opt \
    && rm -rf /opt/embree-3.6.1.x86_64.linux/bin \
    && rm -rf /opt/embree-3.6.1.x86_64.linux/doc \
    && rm embree-3.6.1.x86_64.linux.tar.gz

# install pybind11 headers
RUN curl -SL https://github.com/pybind/pybind11/archive/v2.3.0.tar.gz | tar -xzC /root && \
    cd /root/pybind11-2.3.0 && \
    mkdir build && cd build && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=/usr -DPYBIND11_TEST=off && \
    make install && \
    cd / && rm -rf /root/pybind11-*

# ubuntu qhull doesn't provide qhullcpp, build it by hand
RUN curl -SL https://github.com/qhull/qhull/archive/2019.1.tar.gz | tar -xzC /root && \
    cd /root/qhull-2019.1 && \
    mkdir build2 && cd build2 && \
    cmake ../ -DCMAKE_INSTALL_PREFIX=/usr -DLIB_INSTALL_DIR=/usr/lib/x86_64-linux-gnu -DCMAKE_BUILD_TYPE=Release -DCMAKE_CXX_FLAGS=-fPIC -DCMAKE_C_FLAGS=-fPIC && \
    make install -j 10 && \
    cd / && rm -rf /root/qhull-*

# mount points for filesystems on clusters
RUN mkdir -p /nfs \
    mkdir -p /oasis \
    mkdir -p /scratch \
    mkdir -p /work \
    mkdir -p /projects \
    mkdir -p /home1