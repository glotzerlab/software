TACC Stampede2
--------------

`Stampede2 <https://www.tacc.utexas.edu/systems/stampede2>`_ is an HPC cluster at TACC with CPU nodes.
Apply for resources on Stampede2 through the `XSEDE <https://www.xsede.org/>`_ program.

Stampede2 does not allow singularity on the login nodes. Request an interactive job to pull singularity images::

    ▶ idev -p skx-normal -N 1 -m 30

Wait for the job to start...

.. note::

    Alternately, pull ``shub://glotzerlab/software:stampede2`` on another system and copy the file to stampede2.

The **glotzerlab-software** container is large, store it in your scratch directory::

    ▶ cd $SCRATCH

Pull the container with support for Stampede2::

    ▶ module load tacc-singularity
    ▶ export SINGULARITY_CACHEDIR=$SCRATCH
    ▶ singularity pull --name "software.simg" shub://glotzerlab/software:stampede2
    Progress |===================================| 100.0%
    Done. Container is at: software.simg

Use the following commands in your job scripts or interactively to execute software inside the container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

MPI parallel CPU jobs (``skx-normal`` partition, ``skx-large`` partition, ``skx-dev`` partition)::

    module load tacc-singularity
    module load mvapich2
    ibrun singularity exec $SCRATCH/software.simg command arguments
