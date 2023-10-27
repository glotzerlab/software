Anvil (Purdue)
---------------

Anvil_ is an HPC cluster at NCSA with GPU and CPU nodes. Apply for resources on Anvil through
the ACCESS_ program.

.. _Anvil: https://www.rcac.purdue.edu/knowledge/anvil
.. _ACCESS: https://allocations.access-ci.org

Downloading
***********

The **glotzerlab-software** image and the singularity cache are large, store them in your scratch
directory::

    $ cd $SCRATCH
    $ export SINGULARITY_CACHEDIR=$SCRATCH/.singularity

Download the image with support for Anvil::

    $ singularity pull software.sif docker://glotzerlab/software:anvil

Using
*****

Use the following commands in your job scripts or interactively to execute software inside the
container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

Serial (or multithreaded) CPU jobs::

    mpirun -n 1 singularity exec --bind /anvil $SCRATCH/software.sif command arguments

MPI parallel CPU jobs::

    mpirun singularity exec --bind /anvil $SCRATCH/software.sif command arguments

.. important::

    You must use ``mpirun`` to launch parallel jobs. ``srun`` is not compatible with the MPI library
    installed inside the container.

.. note::

    This container is compatible with ``openmpi/4.0.6`` which is loaded by default on Anvil.

.. attention::

    The container is built with GPU support but GPU jobs have not been tested on Anvil.
