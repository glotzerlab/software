Stampede2 (TACC)
----------------

`Stampede2 <https://www.tacc.utexas.edu/systems/stampede2>`_ is an HPC cluster at TACC with CPU
nodes. Apply for resources on Stampede2 through the `XSEDE <https://www.xsede.org/>`_ program.

Downloading
***********

TACC allows singularity only on compute nodes. To download the latest image, request an interactive
job and run the following commands in the interactive job::

    $ idev -p skx-normal -N 1

Load the singularity module::

    $ module load tacc-singularity

The **glotzerlab-software** image is large, store it in your scratch directory::

    $ cd $SCRATCH

Download the image with support for Stampede2::

    $ singularity pull software.sif docker://glotzerlab/software:stampede2

Or the beta (with HOOMD v3.0.0-beta.X)::

    $ singularity pull software.sif docker://glotzerlab/software:beta-stampede2

Exit the interactive job when you are done:

    $ exit

Using
*****

Use the following commands in your job scripts or interactively to execute software inside the
container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

MPI parallel CPU jobs (``skx-normal`` partition, ``skx-large`` partition, ``skx-dev`` partition)::

    module load tacc-singularity
    module load mvapich2
    ibrun singularity exec $SCRATCH/software.sif command arguments
