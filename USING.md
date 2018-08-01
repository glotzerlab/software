# Glotzerlab software

These images contain software developed and used by the [Glotzer lab](http://glotzerlab.engin.umich.edu/home/), including:

  * [Fresnel](https://bitbucket.org/glotzer/fresnel)
  * [Freud](https://bitbucket.org/glotzer/freud)
  * [GSD](https://bitbucket.org/glotzer/gsd)
  * [HOOMD-blue](http://glotzerlab.engin.umich.edu/hoomd-blue/)
  * [libgetar](https://bitbucket.org/glotzer/libgetar/)
  * [Pythia](https://bitbucket.org/glotzer/pythia/)
  * [Rowan](https://bitbucket.org/glotzer/rowan/)
  * [Plato](https://bitbucket.org/glotzer/plato/)
  * [Signac](http://signac.io)
  * [Signac-flow](http://signac.io)

The images also contain common tools:

  * ffmpeg
  * h5py
  * jupyter
  * LLVM/clang
  * matplotlib
  * mpi4py
  * numpy
  * pandas
  * pillow
  * PyQt5
  * pyyaml
  * pytest
  * python3
  * scipy
  * scikit-learn
  * sphinx

Request additional tool installations by opening an issue at [docker-glotzerlab-software Bitbucket project](https://bitbucket.org/glotzer/docker-glotzerlab-software). Only **standard** tools of general interest to a large number of users belong in the base image. You can [create your own Docker image](https://docs.docker.com/get-started/part2/) to extend the ``glotzerlab/software`` base with your custom tools.

## Tags

The following images are available:

  * ``latest``, ``cuda8`` - Latest image built with CUDA 8.0 (no MPI)
  * ``flux``, ``cuda8-flux`` - Latest image built with CUDA 8.0, MPI, and network drivers for University of Michigan Flux
  * ``comet``, ``cuda8-comet`` - Latest image built with CUDA 8.0, MPI, and network drivers for SDSC Comet
  * ``bridges``, ``cuda8-bridges`` - Latest image built with CUDA 8.0, MPI, and network drivers for PSC Bridges
  * ``stampede2``, ``cuda8-stampede2`` - Latest image built with CUDA 8.0, MPI, and network drivers for TACC Stampede2
  * ``YYYY.MM-cuda?`` - Archived images, built with the indicated versions of CUDA (no MPI)
  * ``YYYY.MM-cuda?-${network}-${mpi}`` - Archived images, built with the indicated versions of CUDA, IB network drivers, and MPI.
  * ``YYYY.MM-cuda?-${cluster}`` - Archived images, built with the indicated versions of CUDA, MPI, and network drivers for the named cluster.

See the tags tab for a list of these archived images.

## Using these images on a single node

Docker images are portable and may be used in many different single node environments.

### Mac, Linux, and cloud resources that you administer

Install and configure docker. You can start an interactive session of the glotzerlab/software image with the following command:

    docker run --rm -it glotzerlab/software

See the [Docker documentation](https://docs.docker.com/) for more information on useful tasks such as bind mounting and executing individual commands.

You can utilize NVIDIA GPUs on local and cloud systems with the NVIDIA container runtime. See the [NVIDIA GPU CLOUD documentation](http://docs.nvidia.com/ngc/index.html#ngc-with-nvidia-titan-pcs) for more information.

    docker run --runtime=nvidia --rm -it glotzerlab/software

### Compute clusters or other multi-user systems with Singularity support

Many compute clusters, including XSEDE Comet, XSEDE Bridges, XSEDE Stampede2, and University of Michigan Flux support singularity. [Singularity](http://singularity.lbl.gov/) can import docker images.

Pull the container to convert it from docker format to singularity format. Set the umask to 002 to avoid a bug in Singularity, and set `SINGULARITY_CACHEDIR` to scratch space (if needed to avoid quota limits on your home directory):

    umask 002
    export SINGULARITY_CACHEDIR="$SCRATCH/.singularity"
    singularity pull docker://glotzerlab/software

You can start an interactive session with the following command:

    singularity shell software.simg

Singularity automatically bind mounts your home directory (and scratch directories on many clusters), so you can easily execute individual commands (i.e. from your job script) like this:

    singularity exec software.simg python3 script.py --arguments

You can utilize NVIDIA GPUs available on the local system:

    singularity exec --nv software.simg python3 script.py --arguments

Note: A bug in singularity 2.4.6 (and possibly other versions) requires that you set ``umask 002`` before using the ``--nv`` option.

### Compute clusters or other multi-user systems with Docker support

Refer to your system's documentation.

## Using these images with MPI

[Singularity](http://singularity.lbl.gov/) supports MPI applications within containers. However, MPI enabled-containers are not fully portable. The MPI libraries on the host and within the container must be compatible, and the container must have the correct drivers installed to access the high performance interconnect.

There are specific tagged versions of the ``glotzerlab/software`` container to support specific clusters. If your cluster is not on the list, try one with a similar interconnect and MPI software version. If that doesn't work, clone the [docker-glotzerlab-software git repository](https://bitbucket.org/glotzer/docker-glotzerlab-software), modify the Dockerfiles accordingly, and build a container for your system.

### SDSC Comet

Comet has OpenMPI 1.8.4 and a Mellanox 4 IB network.

Use Oasis for the singularity cache directory to avoid quota limits on the default home directory:

    export SINGULARITY_CACHEDIR="/oasis/scratch/comet/$USER/temp_project/.singularity"

Pull the container inside an interactive job (pulls on the head node fail with an error message):

    srun --partition=debug --pty --nodes=1 --ntasks-per-node=24 -t 00:30:00 --wait=0 --export=ALL /bin/bash
    # wait for job to start
    module load singularity
    umask 002
    singularity pull docker://glotzerlab/software:comet

Load the appropriate ``openmpi`` module in your job script before launching singularity:

    module load singularity
    module unload mvapich2_ib
    module load openmpi_ib

Use ibrun to launch singularity, which in turn launches a MPI enabled application in the container:

    ibrun singularity exec --nv software-comet.simg python3 script.py

### SDSC Bridges

Bridges has OpenMPI 1.10.4 and an Intel Omni-Path network.

Use Pylon for the singularity cache directory to avoid quota limits on the default home directory:

    export SINGULARITY_CACHEDIR="$SCRATCH/.singularity"

Pull the container with support for Bridges:

    module load singularity
    umask 002
    singularity pull docker://glotzerlab/software:bridges

Load the appropriate ``openmpi`` module in your job script before launching singularity:

    source /etc/profile.d/modules.sh
    module load singularity
    module unload intel
    module load mpi/gcc_openmpi

Use mpirun to launch singularity, which in turn launches a MPI enabled application in the container:

    mpirun singularity exec --nv software-bridges.simg python3 script.py

### TACC Stampede2

Stampede2 has mvapich2.3 and an Intel Omni-Path network.

Use scratch for the singularity cache directory to avoid quota limits on the default home directory:

    export SINGULARITY_CACHEDIR="$SCRATCH/.singularity"

Pull the container inside an interactive job:

    idev -p skx-normal -N 1 -m 30
    # wait for job to start
    module load tacc-singularity
    umask 002
    singularity pull docker://glotzerlab/software:stampede2

Load the appropriate ``mvapich2`` module in your job script before launching singularity:

    module load tacc-singularity
    module load mvapich2

Use ibrun to launch singularity, which in turn launches a MPI enabled application in the container:

    ibrun singularity exec software-stampede2.img python3 script.py

Warning: Executing the container will create a file named "=8.0" in the current working directory. This bug is fixed in newer versions of Singularity and will go away when TACC updates to a recent version.

### University of Michigan Flux

Flux has OpenMPI 3.0 and a Mellanox 4 IB network.

Use scratch for the singularity cache directory to avoid quota limits on the default home directory (replace ${YOUR_ACCOUNT} with your account:

    export SINGULARITY_CACHEDIR="/scratch/${YOUR_ACCOUNT}/${USER}/.singularity"

Pull the container with support for Flux:

    umask 002
    singularity pull docker://glotzerlab/software:flux

Load the appropriate ``openmpi`` module in your job script before launching singularity:

    module load gcc/5.4.0
    module load openmpi/3.0.0/gcc/5.4.0

Use mpirun to launch singularity, which in turn launches a MPI enabled application in the container:

    mpirun singularity exec --nv software-flux.simg python3 script.py

## Building images on OLCF systems

OLCF Titan requires special containers that include a Titan specific version of CUDA and MPI. You can build your own container to run on OLCF Titan using OLCF's [container builder](https://www.olcf.ornl.gov/container-builder/). You will need the ``Dockerfile`` from the ``olcf-titan`` directory of this repository (https://bitbucket.org/glotzer/docker-glotzerlab-software).

    module load container-builder
    container-builder software.img Dockerfile

Run the container with GPU and MPI support (no --nv option needed):

    aprun -N 1 singularity software.img python3 run.py

OLCF documents several [limitations when using singularity on Titan](https://www.olcf.ornl.gov/software-containers-on-titan/).
