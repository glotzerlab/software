# Glotzerlab software

## Docker file overview

This repository hosts Dockerfiles for software developed and used by the [Glotzer
lab](http://glotzerlab.engin.umich.edu/home/). Most of these software packages are python libraries
designed to be used together, so we install it all together in one image and version it by date.
Each image contains the latest versions of all installed software available that month.

These images are hosted on the Docker Hub in the [glotzerlab
organization](https://hub.docker.com/r/glotzerlab/software/): This README is intended for Dockerfile
image developers and those who wish to modify these images.

To prevent combinatorial explosion of the number of images (i.e. multiple MPI versions combined with
multiple CUDA versions), we only introduce new images where absolutely necessary to support a wide
number of users. Supporting dozens of images is not only time consuming to build and test, but also
confusing for users. Individual users that require specific versions can clone this repository, make
the modification, and build their own images.

## Installation scripts

Not all HPC systems support containers. For these systems glotzerlab-software generates installation
scripts from the same templates used for docker.

## Layout

Images are combined from a number of Jinja template files in `template/*.jinja` by the script
`make_dockerfiles.py`. Modifications must be made to the templates, not the generated dockerfiles.

### Base templates

* `template/base.jinja` provides the base dependencies necessary to build Glotzer Lab
  software along with commonly used tools. This image is based on
  `nvidia/cuda-?.?-devel-ubuntu20.04`.
* `frontier.jinja` provides the base dependencies through modules on OLCF Frontier and configures
  a software root directory for the build script.
* `ib-mlx.jinja` adds high speed IB networking drivers.
* `openmpi.jinja` and `mvapich2.jinja` build the corresponding MPI libraries.
* `glotzer-software.jinja` compiles and installs glotzer group software.
* `finalize.jinja` creates a `glotzerlab-software` user so that tools designed to run as
  non-root can run without any user intervention.
* `test.jinja` runs unit tests on some of the installed packages.

### Software images

Images are stored in the docker hub repository `glotzerlab/software`.

The script `make_dockerfiles.py` generates the docker files from the templates and places them under
the `docker/` directory.

* `docker/Dockerfile` - devel image providing dependencies but no software
* `docker/nompi/Dockerfile` - base image with no MPI support
* `docker/${cluster}/Dockerfile` - Add MPI support for a given cluster

### Installation scripts

Build scripts are generated under the `script/` directory for systems that don't support containers.

* `script/frontier/install.sh`

## Building images

### Dependencies

`glotzerlab/software` requires the following Python dependencies
- `jinja2`
- `pyyaml`.

We recommend installing these into a virtual environment with `venv`.

### Building

`build.sh -r repository [ -t tag ] [ system [ system [ ... ] ] ]` builds the images.

* `-r repository` sets the docker repository to label the builds
* `-t` set the tag name (the default is the date in `YYYY-MM` format).
* system is one of the directories in `docker` to build

Here is an example that builds the `nompi` image in a testing repository::

  ./build.sh -r glotzerlab-testing nompi

The CI scripts build and upload the docker containers to the `glotzerlab/software` repository on
Docker Hub.

## Singularity

Users use `singularity pull` to pull the Docker image from Docker Hub and generate a Singularity
image locally for use on HPC systems.

## Benchmarking

The image contains the [OSU microbenchmark suite](http://mvapich.cse.ohio-state.edu/benchmarks/) to
verify proper MPI operation and high speed network performance:

    mpirun -N 1 singularity exec ${IMAGE} /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

## Testing

See: https://glotzerlab-software.readthedocs.io/en/latest/test.html

## Adding a package to the container

The Python packages to install in the container in one of the following files:

  * `requirements.txt` - general packages.
  * `requirements-source.txt` - packages to build from source.
  * `requirements-mpi.txt` - packages that depend on an MPI installation.

Packages not available on PyPI are listed in `packages.yml`.

All packages in the above files are listed with explicit versions.

Steps to add a new package:

1. Add the package as appropriate to `requirements*.txt` or `packages.yml`.
2. Add build scripts for non-PyPI packages to `glotzerlab-software.jinja`.
3. Add unit tests to `test.jinja` if needed.
4. Build and test the image.

## Updating packages in the container

The update process is automatic. Dependabot is configured to update the packages in
`requirements*.txt`. The script `.github/workflows/update-packages.py` updates `packages.yml` and a
GitHub Actions workflow runs this periodically. All changes by CI are submitted as pull requests for
final review before merging.
