Expanse (SDSC)
---------------

Expanse_ is an HPC cluster at SDSC with GPU and CPU nodes. Apply for resources on Expanse through
the XSEDE_ program.

.. _Expanse: https://www.sdsc.edu/support/user_guides/expanse.html
.. _XSEDE: https://www.xsede.org/

Downloading
***********

The **glotzerlab-software** image is large, store it in your project directory::

    $ cd /expanse/lustre/scratch/$USER/temp_project

Download the image with support for Expanse::

    $ singularity pull software.sif docker://glotzerlab/software:expanse

Or the beta (with HOOMD v3.0.0-beta)::

    $ singularity pull software.sif docker://glotzerlab/software:beta-expanse

Using
*****

Use the following commands in your job scripts or interactively to execute software inside the
container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

Serial (or multithreaded) CPU jobs (``shared`` partition)::

    module load cpu singularitypro openmpi/4.1.1
    singularity exec /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

Single GPU jobs (``gpu-shared`` partition)::

    module load gpu singularitypro openmpi/4.1.1
    singularity exec --nv /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

MPI parallel CPU jobs (``compute`` partition, ``shared`` partition with more than 1 core)::

    module load cpu singularitypro openmpi/4.1.1
    mpirun singularity exec /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

MPI parallel GPU jobs (``gpu`` partition, ``gpu-shared`` with more than 1 GPU)::

    module load gpu singularitypro openmpi/4.1.1
    mpirun singularity exec --nv /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments
