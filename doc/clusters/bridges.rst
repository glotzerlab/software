PSC Bridges
-----------

`Bridges <https://psc.edu/resources/computing/bridges>`_ is an HPC cluster at PSC with GPU and CPU nodes.
Apply for resources on Bridges through the `XSEDE <https://www.xsede.org/>`_ program.

The **glotzerlab-software** container is large, store it in your scratch directory::

    ▶ cd $SCRATCH

Pull the container with support for Bridges::

    ▶ module load singularity/2.6.0
    ▶ singularity pull --name "software.simg" shub://glotzerlab/software:bridges
    Progress |===================================| 100.0%
    Done. Container is at: software.simg

.. warning::

    Use ``singularity`` 2.6.0, **not the default 3.0**. Singularity 3.0 will not execute **glotzerlab-software**
    images correctly.

Use the following commands in your job scripts or interactively to execute software inside the container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

Serial (or multithreaded) CPU jobs (``RM-shared`` partitions)::

    source /etc/profile.d/modules.sh
    module load singularity/2.6.0
    mpirun -n 1 singularity exec $SCRATCH/software.simg command arguments

Single GPU jobs (``GPU-shared`` partition)::

    source /etc/profile.d/modules.sh
    module load singularity/2.6.0
    mpirun -n 1 singularity exec --nv $SCRATCH/software.simg command arguments

MPI parallel CPU jobs (``RM`` partition, ``RM-shared`` partition with more than 1 core)::

    source /etc/profile.d/modules.sh
    module load singularity/2.6.0
    module unload intel
    module load mpi/gcc_openmpi
    mpirun singularity exec $SCRATCH/software.simg command arguments

MPI parallel GPU jobs (``GPU`` partition)::

    source /etc/profile.d/modules.sh
    module load singularity/2.6.0
    module unload intel
    module load mpi/gcc_openmpi
    mpirun singularity exec --nv $SCRATCH/software.simg command arguments
