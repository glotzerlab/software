# Glotzerlab docker images

Read this if you want to learn how the glotzerlab software images are built. If you just want to use the images, see the [glotzerlab-software documentation](https://glotzerlab-software.readthedocs.io/).

This repository hosts Dockerfiles for software developed and used by the [Glotzer lab](http://glotzerlab.engin.umich.edu/home/). Most of these software packages are python libraries designed to be used together, so we install it all together in one image and version it by date (YYYY.MM). Each image contains the latest versions of all installed software available that month.

These images are hosted on the Docker Hub in the [glotzerlab organization](https://hub.docker.com/r/glotzerlab/software/): This README is intended for Dockerfile image developers and those who wish to modify these images.

To prevent combinatorial explosion of the number of images (i.e. multiple MPI versions combined with multiple CUDA versions), we only introduce new images where absolutely necessary to support a wide number of users. Supporting dozens of images is not only time consuming to build and test, but also confusing for users. Individual users that require specific versions can clone this repository, make the modification, and build their own images.

## Layout

Images are combined from a number of Jinja template files in ``template/*.jinja`` by the script ``make_dockerfiles.py``. Modifications must be made to the templates, not the generated dockerfiles.

### Base templates

The template ``template/base.jinja`` provides the base dependencies necessary to build Glotzer Lab software along with commonly used tools. This image is based on ``nvidia/cuda-8.0-devel-ubuntu16.04``. Not all clusters support CUDA 9.0 yet, so we start with CUDA 8.0, and ubuntu 16.04 is the current LTS support version (TODO: switch to 18.04 when available).

The templates ``ib-mlx.jinja`` and ``ib-hfi1``.jinja adds high speed IB networking drivers.

The templates ``openmpi.jinja`` and ``mvapich2.jinja`` build the corresponding MPI libraries.

The template ``glotzer-software.jinja`` compiles and installs glotzer group software that doesn't require MPI.
``glotzer-software-mpi.jinja`` installs software that does require MPI. These two sets are separated so that docker can
cache the builds from the first and only need to rebuild the second.

The template ``finalize.jinja`` creates a ``glotzerlab-software`` user so that tools designed to run as non-root can
run without any user intervention.

### Software images

Images are stored in the docker hub repository ``glotzerlab/software``.

For future expansion, images are put in a top level directory named after their base image: Currently ``cuda8`` for the ``nvidia/cuda-8.0-devel-ubuntu16.04`` image above. Additional layers are added in sub directories under the base.

* ``glotzerlab/cuda8/Dockerfile`` - devel image providing dependencies but no software
* ``glotzerlab/cuda8/nompi/Dockerfile`` - base image with no MPI support
* ``glotzerlab/cuda8/${cluster}/Dockerfile`` - Add MPI support for a given cluster

Due to the use of site-specific software, OLCF Titan and Summit require base layers tailored specifically to them. Also, these images must be built within the confines of the [container-builder service at OLCF](https://www.olcf.ornl.gov/container-builder/).

* ``glotzerlab/olcf-titan/Dockerfile``
* ``glotzerlab/olcf-summit/Dockerfile``

## Building images

The ``build.sh`` script builds all of the images and tags them with the current date code.

## Singularity

Singularity's docker pull support is flaky. ``build.sh`` generates a ``Singulartiy`` file for each cluster for
[singularity hub](https://www.singularity-hub.org/) to build. Each just pulls from the docker image that ``build.sh``
produces, so one must ``docker push`` before ``git push``, or the singularity build will fail.

At this time, we do not freeze older versions on singularity hub.

## Benchmarking

The image contains the [OSU microbenchmark suite](http://mvapich.cse.ohio-state.edu/benchmarks/) to verify proper MPI operation and high speed network performance:

    mpirun -N 1 singularity exec ${IMAGE} /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

## Testing

TODO: write test scripts that validate that the image and the software inside works on each tested platform.

## What works (and what doesn't)

Results of testing these images on a number of local and national supercomputer centers.

Updated: 2018-03-20.

* SDSC Comet (w/ Singularity):
    * Serial CPU: working
    * Serial GPU (cuda8): working
    * MPI (comet): working
    * Note: *Running the image will create the file =8.0 in your current working directory. This issue will go away when SDSC updates to a newer version of singularity
* PSC Bridges (w/ Singularity):
    * Serial CPU: working
    * Serial GPU (cuda8): working
    * MPI (bridges): working
* TACC Stampede2 (w/ Singularity)
    * Serial CPU: working
    * MPI (stampede2): working
* OLCF Titan (w/ Singularity):
    * n/a - Singularity has been removed from Titan
* University of Michigan Flux (w/ Singularity):
    * Serial CPU: working
    * Serial GPU (cuda8): working
    * MPI (flux): working (**infiniband enabled on most nodes, but not all**)
* Arch linux workstation (with openmpi 3.0.0 installed):
    * Docker:
        * Serial CPU: working
        * GPU (runtime=nvidia): working
    * Singularity:
        * Serial CPU: working
        * Serial GPU (cuda8): working
        * MPI: **not supported**
