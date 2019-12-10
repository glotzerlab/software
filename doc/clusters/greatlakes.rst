Great Lakes (UMich)
-------------------

`Great Lakes <https://arc-ts.umich.edu/greatlakes/>`_ is the University of Michigan campus cluster.

The **glotzerlab-software** image is large, store it in your scratch directory::

    ▶ cd /scratch/your-account_root/your-account/$USER

.. note::

    replace ``your-account`` with your Great Lakes account name

Download the image with support for Great Lakes::

    ▶ curl -o software.simg https://glotzerlab.engin.umich.edu/downloads/glotzerlab/software-greatlakes.simg

Use the following commands in your job scripts or interactively to execute software inside the container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

Serial (or multithreaded) CPU jobs::

    module load gcc/8.2.0 openmpi/4.0.2 singularity
    mpirun -n 1 singularity exec /scratch/your-account_root/your-account/$USER/software.simg command arguments

Single GPU jobs::

    module load gcc/8.2.0 openmpi/4.0.2 singularity
    mpirun -n 1 singularity exec --nv /scratch/your-account_root/your-account/$USER/software.simg command arguments

MPI parallel CPU jobs::

    module load gcc/8.2.0 openmpi/3.1.4
    mpirun singularity exec /scratch/your-account_root/your-account/$USER/software.simg command arguments

MPI parallel GPU jobs::

    module load gcc/8.2.0 openmpi/3.1.4
    mpirun singularity exec --nv /scratch/your-account_root/your-account/$USER/software.simg command arguments
