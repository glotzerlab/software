# Glotzerlab software

These images contain software developed and used by the [Glotzer lab](http://glotzerlab.engin.umich.edu/home/), including:

  * [Fresnel](https://bitbucket.org/glotzer/fresnel)
  * [Freud](https://bitbucket.org/glotzer/freud)
  * [GSD](https://bitbucket.org/glotzer/gsd)
  * [HOOMD-blue](http://glotzerlab.engin.umich.edu/hoomd-blue/)
  * [Signac](http://signac.io)
  * [Signac-flow](http://signac.io)

The images also contain commonly used tools:

  * LLVM/clang
  * python3

## Tags

The following images are available:

  * ``latest``, ``cuda8`` - Latest image built with CUDA 8.0 (no MPI)
  * ``openmpi3.0``, ``cuda8-openmpi3.0`` - Latest image built with CUDA 8.0 and OpenMPI 3.0
  * ``YYYY.MM-cuda?`` - Archived images, built with the indicated versions of CUDA (no MPI)
  * ``YYYY.MM-cuda?-openmpi?.?`` - Archived images, built with the indicated versions of CUDA and OpenMPI.

See the tags tab for a list of archived images.

## Using these images on a single node

Docker images are portable and may be used in many different environments.

### Mac, Linux, and cloud resources that you control

Install and configure docker. You can start an interactive session with the following command. See the [Docker documentation](https://docs.docker.com/) for more information on useful tasks such as bind mounting and executing individual commands.

    docker run --rm -it glotzerlab/software

You can utilize NVIDIA GPUs on local and cloud systems with the NVIDIA container runtime. See the [NVIDIA GPU CLOUD documentation](http://docs.nvidia.com/ngc/index.html#ngc-with-nvidia-titan-pcs) for more information.

    docker run --runtime=nvidia --rm -it glotzerlab/software

### Compute clusters or other multi-user systems with Singularity support

Many compute clusters, including XSEDE Comet, XSEDE Bridges, XSEDE Stampede2, and University of Michigan Flux support singularity, not docker. [Singularity](http://singularity.lbl.gov/) can import docker images.

Pull the container to convert it from docker format to singularity format. A current bug in singularity requires that you set your umask to 002 before pulling:

    umask 002
    singularity pull docker://glotzerlab/software

You can start an interactive session with the following command (note, your file may have the extension ``.img`` or ``.simg`` depending on the version of singularity you use).

    singularity shell software.simg

Singularity automatically bind mounts your home directory (and scratch directories on many clusters), so you can easily execute individual commands (i.e. from your job script) like this:

    singularity exec software.simg python3 script.py --arguments

You can utilize NVIDIA GPUs available on the local system:

    singularity exec --nv software.simg python3 script.py --arguments

### Compute clusters or other multi-user systems with Docker support

Refer to your system's documentation.

## Using these images with MPI

[Singularity](http://singularity.lbl.gov/) supports MPI applications within containers. The ``glotzerlab/software`` container has **BETA** support for this in images taged ``openmpi3.0``. Currently, this is only tested and supported on the University of Michigan Flux cluster. **Support for other national supercomputing centers may be added in the future**

### University of Michigan Flux

Pull the container with openmpi3 support:

    umask 002
    singularity pull docker://glotzerlab/software:openmpi3.0

To run a HOOMD-blue script with MPI, first you must load the appropriate ``openmpi`` module on flux:

    module load gcc/5.4.0
    module load openmpi/3.0.0/gcc/5.4.0

Then you can use mpirun to launch singularity, which in turn launches a hoomd script inside the container:

    mpirun singularity exec --nv software-openmpi3.0.simg python3 script.py

The image contains the [OSU microbenchmark suite](http://mvapich.cse.ohio-state.edu/benchmarks/) to verify proper MPI operation and high speed network performance:

    mpirun -n 2 singularity exec software-openmpi3.0.simg /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

## Building images on OLCF systems

OLCF Titan requires special containers that include a Titan specific version of CUDA and MPI. You can build your own container to run on OLCF Titan using OLCF's [container builder](https://www.olcf.ornl.gov/container-builder/). You will need the ``Dockerfile`` from the ``olcf-titan`` directory of this repository (https://bitbucket.org/glotzer/docker-glotzerlab-software).

    module load container-builder
    container-builder software.img Dockerfile

And you can run the container with GPU and MPI support:

    aprun -N 1 singularity software.img python3 run.py

OLCF documents several [limitations when using singularity on Titan](https://www.olcf.ornl.gov/software-containers-on-titan/).
