Expanse (SDSC)
---------------

Expanse_ is an HPC cluster at SDSC with GPU and CPU nodes. Apply for resources on Expanse through
the XSEDE_ program.

.. _Expanse: https://www.sdsc.edu/support/user_guides/expanse.html
.. _XSEDE: https://www.xsede.org/

Downloading
***********

Singularity requires more memory than Expanse provides on the login node. Launch an interactive
job with sufficient memory and perform the image pull steps on a compute node::

    $ srun --partition=shared --pty --nodes=1 --ntasks-per-node=1 --mem=8G --time=02:00:00 --wait=0 --export=ALL --account=<your-account> /bin/bash

The **glotzerlab-software** image and the singularity cache are large, store them in your scratch
directory::

    $ cd /expanse/lustre/scratch/$USER/temp_project
    $ export SINGULARITY_CACHEDIR=/expanse/lustre/scratch/$USER/temp_project/.singularity

CPU
+++

Download the image with support for Expanse's CPU nodes::

    $ singularity pull software.sif docker://glotzerlab/software:expanse

Or the beta for CPU nodes (with HOOMD v3.0.0-beta)::

    $ singularity pull software.sif docker://glotzerlab/software:beta-expanse

GPU
+++

Download the image with support for Expanse's GPU nodes::

    $ singularity pull software.sif docker://glotzerlab/software:expanse-gpu

Or the beta for GPU nodes (with HOOMD v3.0.0-beta)::

    $ singularity pull software.sif docker://glotzerlab/software:beta-expanse-gpu

.. important::

    Use the correct image:

    * ``expanse`` on CPU nodes.
    * ``expanse-gpu`` on GPU nodes.

Using
*****

Use the following commands in your job scripts or interactively to execute software inside the
container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

Serial (or multithreaded) CPU jobs (``shared`` partition)::

    module load cpu singularitypro gcc/9.2.0 openmpi/4.1.1
    singularity exec /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

Single GPU jobs (``gpu-shared`` partition)::

    module load gpu singularitypro openmpi/4.0.4
    singularity exec --nv /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

MPI parallel CPU jobs (``compute`` partition, ``shared`` partition with more than 1 core)::

    module load cpu singularitypro gcc/9.2.0 openmpi/4.1.1
    mpirun singularity exec /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

MPI parallel GPU jobs (``gpu`` partition, ``gpu-shared`` with more than 1 GPU)::

    module load gpu singularitypro openmpi/4.0.4
    mpirun singularity exec --nv /expanse/lustre/scratch/$USER/temp_project/software.sif command arguments

.. important::

    Use the correct ``module load`` line for the type of node your job will execute on.
