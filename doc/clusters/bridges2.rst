Bridges-2 (PSC)
---------------

`Bridges-2 <https://www.psc.edu/resources/bridges-2/>`_ is an HPC cluster at PSC with GPU and CPU
nodes. Apply for resources on Bridges through the `XSEDE <https://www.xsede.org/>`_ program.

The **glotzerlab-software** image is large, store it in your project directory::

    $ cd $PROJECT

Download the image with support for Bridges-2::

    $ curl -o software.simg \
      https://glotzerlab.engin.umich.edu/downloads/glotzerlab/software-bridges2.simg

Or the beta (with HOOMD v3.0.0-beta)::

    $ curl -o software.simg \
      https://glotzerlab.engin.umich.edu/downloads/glotzerlab/software-beta-bridges2.simg

Use the following commands in your job scripts or interactively to execute software inside the
container:

.. note::

    replace ``command arguments`` with the command and arguments you wish to run. For example:
    ``python3 script.py``

Serial (or multithreaded) CPU jobs (``RM-shared`` partitions)::

    module load openmpi/4.0.5-gcc10.2.0
    mpirun -n 1 singularity exec $PROJECT/software.simg command arguments

Single GPU jobs (``GPU-shared`` partition)::

    module load openmpi/4.0.5-gcc10.2.0
    mpirun -n 1 singularity exec --nv $PROJECT/software.simg command arguments

MPI parallel CPU jobs (``RM`` partition, ``RM-shared`` partition with more than 1 core)::

    module load openmpi/4.0.5-gcc10.2.0
    mpirun singularity exec $PROJECT/software.simg command arguments

MPI parallel GPU jobs (``GPU`` partition)::

    module load openmpi/4.0.5-gcc10.2.0
    mpirun singularity exec --nv $PROJECT/software.simg command arguments
