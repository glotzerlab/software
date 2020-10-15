Stampede2 (TACC)
----------------

`Stampede2 <https://www.tacc.utexas.edu/systems/stampede2>`_ is an HPC cluster at TACC with CPU nodes.
Apply for resources on Stampede2 through the `XSEDE <https://www.xsede.org/>`_ program.

The **glotzerlab-software** image is large, store it in your scratch directory::

    $ cd $SCRATCH

Download the image with support for Stampede2::

    $ curl -o software.simg https://glotzerlab.engin.umich.edu/downloads/glotzerlab/software-stampede2.simg

Or the beta (with HOOMD v3.0.0-beta)::

    $ curl -o software.simg https://glotzerlab.engin.umich.edu/downloads/glotzerlab/software-beta-stampede2.simg

Use the following commands in your job scripts or interactively to execute software inside the container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

MPI parallel CPU jobs (``skx-normal`` partition, ``skx-large`` partition, ``skx-dev`` partition)::

    module load tacc-singularity
    module load mvapich2
    ibrun singularity exec $SCRATCH/software.simg command arguments
