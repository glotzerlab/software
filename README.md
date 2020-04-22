# Glotzerlab software

Read this if you want to learn how the glotzerlab software images are built. If
you just want to use the images, see the [glotzerlab-software
documentation](https://glotzerlab-software.readthedocs.io/).

## Docker file overview

This repository hosts Dockerfiles for software developed and used by the
[Glotzer lab](http://glotzerlab.engin.umich.edu/home/). Most of these software
packages are python libraries designed to be used together, so we install it all
together in one image and version it by date (YYYY.MM). Each image contains the
latest versions of all installed software available that month.

These images are hosted on the Docker Hub in the [glotzerlab
organization](https://hub.docker.com/r/glotzerlab/software/): This README is
intended for Dockerfile image developers and those who wish to modify these
images.

To prevent combinatorial explosion of the number of images (i.e. multiple MPI
versions combined with multiple CUDA versions), we only introduce new images
where absolutely necessary to support a wide number of users. Supporting dozens
of images is not only time consuming to build and test, but also confusing for
users. Individual users that require specific versions can clone this
repository, make the modification, and build their own images.

## Installation scripts

Not all HPC systems support containers. For these systems glotzerlab-software
generates installation scripts from the same templates used for docker.

## Layout

Images are combined from a number of Jinja template files in
``template/*.jinja`` by the script ``make_dockerfiles.py``. Modifications must
be made to the templates, not the generated dockerfiles.

### Base templates

The template ``template/base.jinja`` provides the base dependencies necessary to
build Glotzer Lab software along with commonly used tools. This image is based
on ``nvidia/cuda-?.0-devel-ubuntu16.04``.

The template ``summit.jinja`` provides the base dependencies through modules on
summit and configures a software root directory for the build script.

The templates ``ib-mlx.jinja`` and ``ib-hfi1``.jinja adds high speed IB
networking drivers.

The templates ``openmpi.jinja`` and ``mvapich2.jinja`` build the corresponding
MPI libraries.

The template ``glotzer-software.jinja`` compiles and installs glotzer group
software.

The template ``finalize.jinja`` creates a ``glotzerlab-software`` user so that
tools designed to run as non-root can run without any user intervention.

### Software images

Images are stored in the docker hub repository ``glotzerlab/software``.

The script ``make_dockerfiles.py`` generates the docker files from the templates
and places them under the ``docker/`` directory.

* ``docker/Dockerfile`` - devel image providing dependencies but no software
* ``docker/nompi/Dockerfile`` - base image with no MPI support
* ``docker/${cluster}/Dockerfile`` - Add MPI support for a given cluster

### Installation scripts

Build scripts are generated under the ``script/`` directory for systems that
don't support containers.

* ``script/summit/install.sh``

## Building images

``build.sh -r repository [ -t tag ] [ -s ] [ -k ] [ system [ system [ ... ] ] ]``
builds the images.

* ``-r repository`` sets the docker repository to label the builds
* ``-t`` set the tag name (the default is the date in ``YYYY-MM`` format).
* ``-s`` enables the docker->singularity conversion and copying the images to
  ``/nfs/turbo/glotzer/containers/${repository}``
* ``-k`` skips building the docker image
* system is one of the directories in ``docker`` to build

## Singularity

Singularity's docker pull support is flaky. When requested, ``build.sh``
generates a ``Singulartiy`` image file for each cluster using docker2singularity
and stores them in ``/nfs/turbo/glotzer/containers/${repository}``. ``sync.sh``
uploads these to https://glotzerlab.engin.umich.edu/downloads/glotzerlab for
distribution.

Previous builds are not available for download. Users are strongly encouraged to
use the latest images. If users need a previous image, they can build it from
the archive on Docker hub.

## Benchmarking

The image contains the [OSU microbenchmark
suite](http://mvapich.cse.ohio-state.edu/benchmarks/) to verify proper MPI
operation and high speed network performance:

    mpirun -N 1 singularity exec ${IMAGE} /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

## Testing

See: https://glotzerlab-software.readthedocs.io/en/latest/test.html

## Updating a package in the container

`make_dockerfiles.py` stores the version numbers and SHAs of the tarballs in
`versions` and `shas` respectively. These are expanded in the jinja templates.
Many packages need to be built from source so that they (1) are linked to the
cluster specific MPI library provided by the container and (2) link with the
proper ABI and use the libraries provided by `apt-get` in `base.jinja`.

In particular, `glotzerlab-software.jinja` installs a number of python packages
using `python3 -m pip install --no-deps --ignore-installed source-dir`. It does
this to prevent `pip` from pulling in a large dependency tree and overwriting
packages already installed with versions that may have ABI compatibility
issues (e.g. mpi4py, pyside).

To update a package to a new release:

1. Update `version` and `sha` in `make_dockerfiles.py`
2. Add any new dependencies to `base.jinja`. Prefer `apt-get` installations when
   an Ubuntu package exists. If not, add to the `pip install` line, but double
   check the build output to ensure it doesn't result in overwriting the
   `apt-get` installed packages.
3. Build and test the image.
