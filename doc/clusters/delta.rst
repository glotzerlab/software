Delta (NCSA)
------------

Delta_ is an HPC cluster at NCSA with GPU and CPU nodes. Apply for resources on Delta through
the ACCESS_ program.

.. _Delta: https://wiki.ncsa.illinois.edu/display/DSC/Delta+User+Guide
.. _ACCESS: https://allocations.access-ci.org

Downloading
***********

The **glotzerlab-software** image and the singularity cache are large, store them in your scratch
directory::

    $ cd /scratch/<your-account>/$USER/
    $ export APPTAINER_CACHEDIR=/scratch/<your-account>/$USER/.apptainer

.. note::

    Replace ``<your-account>`` with your NCSA account name.

Download the image with support for Delta::

    $ singularity pull software.sif docker://glotzerlab/software:delta

Using
*****

Use the following commands in your job scripts or interactively to execute software inside the
container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

Serial (or multithreaded) CPU jobs (``cpu`` partition)::

    module load gcc/11.2.0 openmpi/4.1.4
    srun -n 1 singularity exec --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

Single GPU jobs (``gpuA100x4`` and similar partitions)::

    module load gcc/11.2.0 openmpi/4.1.4
    srun -n 1 singularity exec --nv --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

MPI parallel CPU jobs (``cpu`` partition with more than 1 core)::

    module load gcc/11.2.0 openmpi/4.1.4
    export OMPI_MCA_btl=self
    srun singularity exec --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

MPI parallel GPU jobs (``gpuA100x4`` and similar partitions with more than 1 GPU)::

    module load gcc/11.2.0 openmpi/4.1.4
    export OMPI_MCA_btl=self
    srun singularity exec --nv --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

.. note::

    Setting ``OMPI_MCA_btl=self`` prevents the warning:
    ```
    UCX  WARN  IB: ibv_fork_init() was disabled or failed, yet a fork() has been issued.
    UCX  WARN  IB: data corruption might occur when using registered memory.
    ```
    OpenMPI uses ``ucx`` for internode communication and skips ``btl`` on Delta.

.. tip::

    You may use ``mpirun -x UCX_POSIX_USE_PROC_LINK=n`` in place of ``srun`` on Delta.
