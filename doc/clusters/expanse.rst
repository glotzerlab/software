Expanse (SDSC)
**************

Expanse_ is an HPC cluster at SDSC with GPU and CPU nodes. Apply for resources on Expanse through
the ACCESS_ program.

.. _Expanse: https://www.sdsc.edu/support/user_guides/expanse.html
.. _ACCESS: https://allocations.access-ci.org/

For unknown reasons, ``singularity pull`` generates corrupt images when run on Expanse. You need
to use another Linux system to pull the ``expanse`` or ``expanse-gpu`` image, then copy that image
to Expanse.

.. note::

    The corrupt image causes ``/usr/<some_file>.so: file too short`` error messages when you
    attempt to use software in the container.

Download the image with support for Expanse's CPU nodes::

    $ singularity pull software.sif docker://glotzerlab/software:expanse

Then copy ``software.sif`` to ``/expanse/lustre/scratch/$USER/temp_project/`` on Expanse.

Or: download the image with support for Expanse's GPU nodes::

    $ singularity pull software.sif docker://glotzerlab/software:expanse-gpu

Then copy ``software.sif`` to ``/expanse/lustre/scratch/$USER/temp_project/`` on Expanse.

.. important::

    Use the correct image:

    * ``expanse`` on CPU nodes.
    * ``expanse-gpu`` on GPU nodes.

Use the following commands in your job scripts or interactively to execute software inside the
container:

.. note::

    Replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``.

Serial (or multithreaded) CPU jobs (``shared`` partition)::

    module load cpu/0.15.4 singularitypro gcc/9.2.0 openmpi/4.1.1
    singularity exec --bind /expanse /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

Single GPU jobs (``gpu-shared`` partition)::

    module load gpu/0.15.4 singularitypro openmpi/4.0.4-nocuda
    singularity exec --nv --bind /expanse /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

MPI parallel CPU jobs (``compute`` partition, ``shared`` partition with more than 1 core)::

    module load cpu/0.15.4 singularitypro gcc/9.2.0 openmpi/4.1.1
    mpirun singularity exec --bind /expanse /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

MPI parallel GPU jobs (``gpu`` partition, ``gpu-shared`` with more than 1 GPU)::

    module load gpu/0.15.4 singularitypro openmpi/4.0.4-nocuda
    mpirun singularity exec --nv --bind /expanse /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

.. important::

    Use the correct ``module load`` line for the type of node your job will execute on.

.. warning::

    ``mpirun`` will hang when launching jobs one more than one node in the ``gpu`` partition.

.. important::

    You must use ``mpirun`` to launch parallel jobs. ``srun`` is not compatible with the MPI library
    installed inside the container.
