Glotzerlab software images
++++++++++++++++++++++++++

**glotzerlab-software** is a set of container images that provide software developed by the
`Glotzer group <http://glotzerlab.engin.umich.edu>`_ at the `University of Michigan <https://www.umich.edu/>`_ along
with related software commonly used in simulation and data analysis workflows. An *image* bundles these tools into
a single file which can be copied, moved, shared with others, and published to provide a completely
reproducible workflow. A *host* system provides the resources to execute software inside containers.
`Singularity <https://www.sylabs.io/docs/>`_ provides a high performance solution, supporting NVIDIA GPUs and MPI
parallel execution. Singularity is available on most HPC resources. You can install it on your linux system if you have
root access.

Quick start
===========

First, download the **glotzerlab/software** image::

    $ curl -o software.simg https://glotzerlab.engin.umich.edu/downloads/glotzerlab/software-nompi.simg

.. note::

    On HPC clusters, download the cluster specific image. See :doc:`cluster` for details.

**singularity exec** executes software from inside the container::

    $ singularity exec software.simg python3 --version
    Python 3.5.2

Add the ``--nv`` option to **enable NVIDIA GPUs** inside the container::

    $ singularity exec --nv software.simg nvidia-smi
    Thu Sep 13 16:49:15 2018
    +-----------------------------------------------------------------------------+
    | NVIDIA-SMI 396.54                 Driver Version: 396.54                    |
    |-------------------------------+----------------------+----------------------+
    | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
    |===============================+======================+======================|
    |   0  Quadro GP100        Off  | 00000000:03:00.0 Off |                  Off |
    | 33%   50C    P0    37W / 235W |      2MiB / 16278MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+

**singularity shell** launches an interactive shell::

    $ singularity shell --nv software.simg
    Singularity: Invoking an interactive shell within container...

    Singularity software.simg:~> python3
    Python 3.5.2 (default, Nov 23 2017, 16:37:01)
    [GCC 5.4.0 20160609] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import hoomd
    >>> import freud
    >>> import signac
    >>> hoomd.context.initialize()
    HOOMD-blue 2.3.4 CUDA (8.0) DOUBLE HPMC_MIXED TBB SSE SSE2
    Compiled: 09/12/18
    Copyright 2009-2018 The Regents of the University of Michigan.
    HOOMD-blue is running on the following GPU(s):
     [0]          Quadro GP100  56 SM_6.0 @ 1.44 GHz, 16278 MiB DRAM

**glotzerlab-software** :doc:`updates monthly <changes>` with the latest versions of included software.
Download the latest image to update::

    $ curl -o software.simg https://glotzerlab.engin.umich.edu/downloads/glotzerlab/software-nompi.simg

.. seealso::

    See the `Singularity documentation <https://www.sylabs.io/docs/>`_ for more information on ``singularity`` commands.

Documentation
_____________

.. toctree::
    :maxdepth: 2

    software
    cluster
    files
    test
    docker
    community
    changes
    license
