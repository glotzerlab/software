Great Lakes (UMich)
-------------------

`Great Lakes <https://arc-ts.umich.edu/greatlakes/>`_ is the University of Michigan campus cluster.

Downloading
***********

The **glotzerlab-software** image and the singularity cache are large, store them in your scratch
directory::

    $ cd /scratch/<your-account_root>/<your-account>/$USER
    $ export SINGULARITY_CACHEDIR=/scratch/<your-account_root>/<your-account>/$USER/.singularity

.. note::

    Replace ``<your-account>`` with your Great Lakes account name.

Download the image with support for Great Lakes::

    $ singularity pull software.sif docker://glotzerlab/software:greatlakes

Using
*****

Use the following commands in your job scripts or interactively to execute software inside the container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

Serial (or multithreaded) CPU jobs::

    module load gcc/10.3.0 openmpi/4.1.6 singularity
    mpirun -n 1 singularity exec --bind /scratch,/gpfs \
      /scratch/your-account_root/your-account/$USER/software.sif command arguments

Single GPU jobs::

    module load gcc/10.3.0 openmpi/4.1.6 singularity
    mpirun -n 1 singularity exec --bind /scratch,/gpfs --nv \
      /scratch/your-account_root/your-account/$USER/software.sif command arguments

MPI parallel CPU jobs::

    module load gcc/10.3.0 openmpi/4.1.6 singularity
    mpirun singularity exec --bind /scratch,/gpfs \
      /scratch/your-account_root/your-account/$USER/software.sif command arguments

MPI parallel GPU jobs::

    module load gcc/10.3.0 openmpi/4.1.6 singularity
    mpirun singularity exec --bind /scratch,/gpfs --nv \
      /scratch/your-account_root/your-account/$USER/software.sif command arguments
