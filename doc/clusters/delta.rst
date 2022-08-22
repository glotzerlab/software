Delta (NCSA)
------------

Delta_ is an HPC cluster at NCSA with GPU and CPU nodes. Apply for resources on Delta through
the XSEDE_ program.

.. _Delta: https://wiki.ncsa.illinois.edu/display/DSC/Delta+User+Guide
.. _XSEDE: https://www.xsede.org/

Downloading
***********

The **glotzerlab-software** image and the singularity cache are large, store them in your scratch
directory::

    $ cd /scratch/<your-account>/$USER/
    $ export APPTAINER_CACHEDIR=/scratch/<your-account>/$USER/.apptainer

.. note::

    Replace ``<your-account>`` with your Great Lakes account name.

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

    module load cpu gcc/11.2.0 openmpi/4.1.2
    mpirun -n 1 singularity exec --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

Single GPU jobs (``gpuA100x4`` and similar partitions)::

    module load gpu gcc/11.2.0 openmpi/4.1.2
    mpirun -n 1 singularity exec --nv --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

MPI parallel CPU jobs (``cpu`` partition with more than 1 core)::

    module load cpu gcc/11.2.0 openmpi/4.1.2
    mpirun singularity exec --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

MPI parallel GPU jobs (``gpuA100x4`` and similar partitions with more than 1 GPU)::

    module load gpu gcc/11.2.0 openmpi/4.1.2
    mpirun singularity exec --nv --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments

.. tip::

    You may use ``srun`` in place of ``mpirun`` on Delta. Set the environment variable
    ``PMIX_MCA_gds=hash`` before launching processes with ``srun``::

        export PMIX_MCA_gds=hash
        srun singularity exec --nv --bind /scratch /scratch/<your-account>/$USER/software.sif command arguments
