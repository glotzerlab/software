# Glotzerlab software

These images contain software developed and used by the [Glotzer lab](http://glotzerlab.engin.umich.edu/home/), along with common tools used in simulation and analysis workflows. See the [glotzerlab-software documentation](https://glotzerlab-software.readthedocs.io/) for details on using these images.

## Tags

The following images are available on docker hub:

  * ``latest`` - Latest image built without MPI
  * ``flux`` - Latest image built with CUDA 8.0, MPI, and network drivers for University of Michigan Flux
  * ``comet`` - Latest image built with CUDA 8.0, MPI, and network drivers for SDSC Comet
  * ``bridges`` - Latest image built with CUDA 8.0, MPI, and network drivers for PSC Bridges
  * ``stampede2`` - Latest image built with CUDA 8.0, MPI, and network drivers for TACC Stampede2
  * ``YYYY.MM-{cpu-arch}-cuda?-${network}-${mpi}`` - Archived images, built for the indicated cpu architecture and the given versions of CUDA, IB network drivers, and MPI.

See the tags tab for a list of these archived images.
