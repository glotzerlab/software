# Glotzerlab docker images

Read this if you want to learn how the glotzerlab software images are built. If you just want to use the images, see [USING.md](USING.md)

This repository hosts Dockerfiles for software developed and used by the [Glotzer lab](http://glotzerlab.engin.umich.edu/home/). Most of these software packages are python libraries designed to be used together, so we install it all together in one image and version it by date (YYYY.MM). Each image contains the latest versions of all installed software available at the beginning of that month.

These images are hosted on the Docker Hub in the [glotzerlab organization](https://hub.docker.com/r/glotzerlab/software/): This README is intended for Dockerfile image developers and those who wish to modify these images.

To prevent combinatorial explosion of the number of images (i.e. multiple MPI versions combined with multiple CUDA versions), we only introduce new images where absolutely necessary to support a wide number of users. Supporting dozens of images is not only time consuming to build and test, but also confusing for users. Individual users that require specific versions can clone this repository, make the modification, and build their own images.

## Layout

Images are combined from a number of Jinja template files in ``template/*.jinja`` by the script ``make_dockerfiles.py``. Modifications must be made to the templates, not the generated dockerfiles.

### Base templates

The template ``template/base.jinja`` provides the base dependencies necessary to build Glotzer Lab software along with commonly used tools. This image is based on ``nvidia/cuda-8.0-devel-ubuntu16.04``. Not all clusters support CUDA 9.0 yet, so we start with CUDA 8.0, and ubuntu 16.04 is the current LTS support version (TODO: switch to 18.04 when available).

The template ``template/openmpi.jinja`` adds openmpi to the base.

We do not separately publish the base and base+MPI images. Doing so adds complexity, and users who wish to build their own images will want to start from their own custom base image. This way, the only glotzerlab docker images published are those containing the group software stack.

### Software images

Images are stored in the docker hub repository ``glotzerlab/software``.

For future expansion, images are put in a top level directory named after their base image: Currently ``cuda8`` for the ``nvidia/cuda-8.0-devel-ubuntu16.04`` image above. Additional layers are added in sub directories under the base.

* ``glotzerlab/cuda8/Dockerfile`` - base image with no MPI support
* ``glotzerlab/cuda8/openmpi3.0/Dockerfile`` - Add OpenMPI 3.0

Due to the use of site-specific software, OLCF Titan and Summit require base layers tailored specifically to them. Also, these images must be built within the confines of the [container-builder service at OLCF](https://www.olcf.ornl.gov/container-builder/).

* ``glotzerlab/olcf-titan/Dockerfile``
* ``glotzerlab/olcf-summit/Dockerfile``

## Building images

The ``build.sh`` script builds all of the images and tags them with the current date code.

TODO: consider how to support OptiX for fresnel.

## What works (and what doesn't)

Results of testing these images on a number of local and national supercomputer centers.

Updated: 2018-03-20.

* SDSC Comet (w/ Singularity):
    * Serial CPU: working
    * GPU (cuda8): working
    * MPI (openmpi3.0): **not supported**
    * Note: *Running the image will create the file =8.0 in your current working directory. Requested singularity upgrade
      to fix this issue.*
* PSC Bridges (w/ Singularity):
    * Serial CPU: working
    * GPU (cuda8): working
    * MPI (openmpi3.0): **not supported**
* TACC Stampede2 (w/ Singularity)
    * **status unknown**, stampede2 was down for maintenance at time of testing
* OLCF Titan (w/ Singularity):
    * Serial CPU: n/a - Titan only runs jobs with aprun
    * GPU (olcf container-builder): working
    * MPI (olcf container-builder): working
* University of Michigan Flux (w/ Singularity):
    * Serial CPU: working
    * GPU (cuda8): working
    * MPI (openmpi3.0): working (**infiniband enabled on most nodes, but not all**)
    * Note: *Running the image will create the file =8.0 in your current working directory. Requested singularity upgrade
      to fix this issue.*
* Arch linux workstation (with openmpi 3.0.0 installed):
    * Docker:
        * Serial CPU: working
        * GPU (runtime=nvidia): working
    * Singularity:
        * Serial CPU: working
        * GPU (cuda8): working
        * MPI (openmpi3.0): **not working, hangs when launching HOOMD with mpirun**
