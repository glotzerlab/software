UMich Flux
----------

Pull the container with support for Flux::

    ▶ singularity pull --name "software.simg" shub://glotzerlab/software:flux
    Progress |===================================| 100.0%
    Done. Container is at: software.simg

.. rubric:: Serial jobs




Load the appropriate ``openmpi`` module in your job script before launching singularity:

    module load gcc/5.4.0
    module load openmpi/3.0.0/gcc/5.4.0

Use mpirun to launch singularity, which in turn launches a MPI enabled application in the container:

    mpirun singularity exec --nv software-flux.simg python3 script.py
