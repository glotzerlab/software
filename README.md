# Glotzerlab software

Read this if you want to learn how the glotzerlab software images are built. If you just want to use the images, see the [glotzerlab-software documentation](https://glotzerlab-software.readthedocs.io/).

## Docker file overview

This repository hosts Dockerfiles for software developed and used by the [Glotzer lab](http://glotzerlab.engin.umich.edu/home/). Most of these software packages are python libraries designed to be used together, so we install it all together in one image and version it by date (YYYY.MM). Each image contains the latest versions of all installed software available that month.

These images are hosted on the Docker Hub in the [glotzerlab organization](https://hub.docker.com/r/glotzerlab/software/): This README is intended for Dockerfile image developers and those who wish to modify these images.

To prevent combinatorial explosion of the number of images (i.e. multiple MPI versions combined with multiple CUDA versions), we only introduce new images where absolutely necessary to support a wide number of users. Supporting dozens of images is not only time consuming to build and test, but also confusing for users. Individual users that require specific versions can clone this repository, make the modification, and build their own images.

## Installation scripts

Not all HPC systems support containers. For these systems glotzerlab-software generates installation scripts from the same templates used for docker.

## Layout

Images are combined from a number of Jinja template files in ``template/*.jinja`` by the script ``make_dockerfiles.py``. Modifications must be made to the templates, not the generated dockerfiles.

### Base templates

The template ``template/base.jinja`` provides the base dependencies necessary to build Glotzer Lab software along with commonly used tools. This image is based on ``nvidia/cuda-?.0-devel-ubuntu16.04``.

The template ``summit.jinja`` provides the base dependencies through modules on summit and configures a software root directory for the build script.

The templates ``ib-mlx.jinja`` and ``ib-hfi1``.jinja adds high speed IB networking drivers.

The templates ``openmpi.jinja`` and ``mvapich2.jinja`` build the corresponding MPI libraries.

The template ``glotzer-software.jinja`` compiles and installs glotzer group software.

The template ``finalize.jinja`` creates a ``glotzerlab-software`` user so that tools designed to run as non-root can
run without any user intervention.

### Software images

Images are stored in the docker hub repository ``glotzerlab/software``.

The script ``make_dockerfiles.py`` generates the docker files from the templates and places them under the ``docker/`` directory.

* ``docker/Dockerfile`` - devel image providing dependencies but no software
* ``docker/nompi/Dockerfile`` - base image with no MPI support
* ``docker/${cluster}/Dockerfile`` - Add MPI support for a given cluster

### Installation scripts

Build scripts are generated under the ``script/`` directory for systems that don't support containers.

* ``script/titan/install.sh``
* ``script/summit/install.sh``

## Building images

The ``build.sh`` script builds all of the images and tags them with the current date code.

## Singularity

Singularity's docker pull support is flaky. ``build.sh`` generates a ``Singulartiy`` file for each cluster for
[singularity hub](https://www.singularity-hub.org/) to build. Each just pulls from the docker image that ``build.sh``
produces, so one must ``docker push`` before ``git push``, or the singularity build will fail.

Previous builds are not frozen on singularity hub. Users are strongly encouraged to use the latest images, but sometimes
there is reason to delay updating. If users need a previous image, they can build it from the archive on Docker hub.

## Benchmarking

The image contains the [OSU microbenchmark suite](http://mvapich.cse.ohio-state.edu/benchmarks/) to verify proper MPI operation and high speed network performance:

    mpirun -N 1 singularity exec ${IMAGE} /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

## Testing

See: https://glotzerlab-software.readthedocs.io/en/latest/test.html
