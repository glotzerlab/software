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

    Replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``.

Serial (or multithreaded) CPU jobs::

    module load gcc/10.3.0 openmpi/4.1.6 singularity
    srun -u --export=ALL -n 1 singularity exec --bind /scratch,/gpfs \
      /scratch/your-account_root/your-account/$USER/software.sif command arguments

Single GPU jobs::

    module load gcc/10.3.0 openmpi/4.1.6 singularity
    srun -u --export=ALL -n 1 singularity exec --bind /scratch,/gpfs --nv \
      /scratch/your-account_root/your-account/$USER/software.sif command arguments

MPI parallel CPU jobs::

    module load gcc/10.3.0 openmpi/4.1.6 singularity
    srun -u --export=ALL singularity exec --bind /scratch,/gpfs \
      /scratch/your-account_root/your-account/$USER/software.sif command arguments

MPI parallel GPU jobs::

    module load gcc/10.3.0 openmpi/4.1.6 singularity
    srun -u --export=ALL singularity exec --bind /scratch,/gpfs --nv \
      /scratch/your-account_root/your-account/$USER/software.sif command arguments

.. important::

    Invoke parallel jobs with ``srun -u --export=ALL`` to ensure proper task distribution to the
    requested resources (``mpirun`` oversubscribes resources in some cases). The ``--export=ALL``
    should be the default behavior but is not observed in testing. The ``-u`` option ensures that
    the stdout and stderr output is written to the file immediately. Without ``-u``, srun on Great
    Lakes tends to buffer output until the job completes.
