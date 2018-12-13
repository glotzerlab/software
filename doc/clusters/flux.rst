Flux (UMich)
------------

`Flux <https://arc-ts.umich.edu/flux/>`_ is the University of Michigan campus cluster.

The **glotzerlab-software** container is large, store it in your scratch directory::

    ▶ cd /scratch/your-account/$USER

.. note::

    replace ``your-account`` with your flux account name

Pull the container with support for Flux::

    ▶ singularity pull --name "software.simg" shub://glotzerlab/software:flux
    Progress |===================================| 100.0%
    Done. Container is at: software.simg

Use the following commands in your job scripts or interactively to execute software inside the container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

Serial (or multithreaded) CPU jobs::

    singularity exec /scratch/your-account/$USER/software.simg command arguments

Single GPU jobs::

    singularity exec --nv /scratch/your-account/$USER/software.simg command arguments

MPI parallel CPU jobs::

    module load gcc/5.4.0
    module load openmpi/3.0.0/gcc/5.4.0
    mpirun singularity exec /scratch/your-account/$USER/software.simg command arguments

MPI parallel GPU jobs::

    module load gcc/5.4.0
    module load openmpi/3.0.0/gcc/5.4.0
    mpirun singularity exec --nv /scratch/your-account/$USER/software.simg command arguments
