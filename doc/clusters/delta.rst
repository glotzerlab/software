Delta (NCSA)
*************

Delta_ is an HPC cluster at NCSA with GPU and CPU nodes. Apply for resources on Delta through
the ACCESS_ program.

.. _Delta: https://ncsa-delta-doc.readthedocs-hosted.com
.. _ACCESS: https://allocations.access-ci.org

The **glotzerlab-software** image and the singularity cache are large, store them in your scratch
directory::

    $ cd /scratch/<your-account>/$USER/
    $ export APPTAINER_CACHEDIR=/scratch/<your-account>/$USER/.apptainer

.. note::

    Replace ``<your-account>`` with your NCSA account name.

Download the image with support for Delta::

    $ singularity pull software.sif docker://glotzerlab/software:delta

Use the following commands in your job scripts or interactively to execute software inside the
container:

.. note::

    Replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``.

Serial (or multithreaded) CPU jobs (``cpu`` partition)::

    module load gcc/11.4.0 openmpi/4.1.6
    mpirun -n 1 singularity exec --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

Single GPU jobs (``gpuA100x4`` and similar partitions)::

    module load gcc/11.4.0 openmpi/4.1.6
    mpirun -n 1 singularity exec --nv --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

MPI parallel CPU jobs (``cpu`` partition with more than 1 core)::

    module load gcc/11.4.0 openmpi/4.1.6
    mpirun singularity exec --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

MPI parallel GPU jobs (``gpuA100x4`` and similar partitions with more than 1 GPU)::

    module load gcc/11.4.0 openmpi/4.1.6
    mpirun singularity exec --nv --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments
