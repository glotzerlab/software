Container images
================

**glotzerlab-software** is a set of container images that provide software developed by the `Glotzer
group <http://glotzerlab.engin.umich.edu>`_ at the `University of Michigan
<https://www.umich.edu/>`_ along with related software commonly used in simulation and data analysis
workflows. An *image* bundles these tools into a single file which can be copied, moved, shared with
others, and published to provide a completely reproducible workflow. A *host* system provides the
resources to execute software inside containers. `Singularity <https://www.sylabs.io/docs/>`_
provides a high performance solution, supporting NVIDIA GPUs and MPI parallel execution. Singularity
is available on most HPC resources. You can install it on your linux system if you have root access.

To use a container, download the **glotzerlab/software** image::

    $ singularity pull software.sif docker://glotzerlab/software

.. note::

    On HPC clusters, download the cluster specific image. See :doc:`cluster` for details.

**singularity exec** executes software from inside the container. For example, run a Python script
with::

    $ singularity exec software.sif python3 script.py

Add the ``--nv`` option to **enable NVIDIA GPUs** inside the container::

    $ singularity exec --nv software.sif nvidia-smi
    +-----------------------------------------------------------------------------+
    | NVIDIA-SMI 450.57       Driver Version: 450.57       CUDA Version: 11.0     |
    |-------------------------------+----------------------+----------------------+
    | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
    |                               |                      |               MIG M. |
    |===============================+======================+======================|
    |   0  Quadro RTX 5000     On   | 00000000:02:00.0 Off |                  Off |
    | 33%   29C    P8    16W / 230W |      1MiB / 16124MiB |      0%      Default |
    |                               |                      |                  N/A |
    +-------------------------------+----------------------+----------------------+

**singularity shell** launches an interactive shell::

    $ singularity shell --nv software.sif
    Singularity: Invoking an interactive shell within container...

    Singularity> python3
    Python 3.6.9 (default, Oct  8 2020, 12:12:24)
    [GCC 8.4.0] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import hoomd
    >>> import freud
    >>> import signac
    >>> gpu = hoomd.device.GPU()
    >>> print(gpu.devices)
    ['[0]       Quadro RTX 5000  48 SM_7.5 @ 1.82 GHz, 16124 MiB DRAM']
    >>>

**glotzerlab-software** updates weekly with the latest versions of included
software. Download the latest image to update::

    $ singularity pull software.sif docker://glotzerlab/software

Environment variables set in the image identify the build::

    $ singularity exec software.sif bash -c "set" | grep GLOTZERLAB
    GLOTZERLAB_SOFTWARE_CONFIGURATION=nompi
    GLOTZERLAB_SOFTWARE_GIT_BRANCH=trunk
    GLOTZERLAB_SOFTWARE_GIT_SHA=f2debd75280c98ed0a4e46e3e2d381e953b80b6f
    GLOTZERLAB_SOFTWARE_TAG=2021.03.24

.. seealso::

    See the `Singularity documentation <https://www.sylabs.io/docs/>`_ for more information on
    ``singularity`` commands.

.. toctree::
    :maxdepth: 1

    software
    cluster
    files
    profiling
    test
    docker
    community
