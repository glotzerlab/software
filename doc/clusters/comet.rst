Comet (SDSC)
------------

`Comet <https://www.sdsc.edu/support/user_guides/comet.html>`_ is an HPC cluster at SDSC with GPU
and CPU nodes. Apply for resources on Comet through the `XSEDE <https://www.xsede.org/>`_ program.

The **glotzerlab-software** image is large, store it in your scratch directory::

    $ cd /oasis/scratch/comet/$USER/temp_project

Download the image with support for Comet::

    $ module load singularity
    $ curl -o software.simg https://glotzerlab.engin.umich.edu/downloads/glotzerlab/software-comet.simg

Or the beta (with HOOMD v3.0.0-beta)::

    $ curl -o software.simg https://glotzerlab.engin.umich.edu/downloads/glotzerlab/software-beta-comet.simg

Use the following commands in your job scripts or interactively to execute software inside the
container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

Serial (or multithreaded) CPU jobs (``shared`` partition)::

    module load singularity
    module unload mvapich2_ib
    module load openmpi_ib
    ibrun -n 1 singularity exec /oasis/scratch/comet/$USER/temp_project/software.simg command arguments

Single GPU jobs (``gpu-shared`` partition)::

    module load singularity
    module unload mvapich2_ib
    module load openmpi_ib
    ibrun -n 1 singularity exec --nv /oasis/scratch/comet/$USER/temp_project/software.simg command arguments

MPI parallel CPU jobs (``compute`` partition, ``shared`` partition with more than 1 core)::

    module load singularity
    module unload mvapich2_ib
    module load openmpi_ib
    ibrun singularity exec /oasis/scratch/comet/$USER/temp_project/software.simg command arguments

MPI parallel GPU jobs (``gpu`` partition)::

    module load singularity
    module unload mvapich2_ib
    module load openmpi_ib
    ibrun singularity exec --nv /oasis/scratch/comet/$USER/temp_project/software.simg command arguments
