Tests
-----

**glotzerlab-software** provides a set of test jobs to determine the installed software functions and that MPI-enabled
software inter-operates with the host system.

Copy the test scripts to the current directory::

    $ singularity exec software.sif bash -c "cp /test/* ."

.. note::

    The test scripts assume the image is named ``software.sif`` and is the same directory.

Submit the test jobs::

    $ sbatch -A <your-account> job-cpu.sh
    $ sbatch -A <your-account> job-gpu.sh

.. note::

    Replace ``sbatch`` with the appropriate queue submission command if necessary.

After the jobs complete, examine the test output. Here example output::

    + singularity exec software.sif bash -c set
    + grep GLOTZERLAB
    GLOTZERLAB_SOFTWARE_CONFIGURATION=bridges2
    GLOTZERLAB_SOFTWARE_GIT_BRANCH=trunk
    GLOTZERLAB_SOFTWARE_GIT_SHA=2327dce1a5cf37351abca48d44a39b93359e55ad
    GLOTZERLAB_SOFTWARE_TAG=2022.08.19
    + mpirun -n 1 singularity exec software.sif python3 serial-cpu.py
    ** Starting serial CPU tests **
    Fresnel version   : 0.13.4
    Fresnel device    : <fresnel.Device: All available CPU threads>
    Freud version     : 2.11.0
    garnett version       : 0.7.1
    GSD version       : 2.6.0
    HOOMD version     : 3.4.0
    HOOMD flags       : GPU [CUDA] (11.1) DOUBLE HPMC_MIXED MPI TBB SSE SSE2 SSE3 SSE4_1 SSE4_2 AVX AVX2
    pythia version    : 0.3.0
    plato version     : 1.12.0
    rowan version     : 1.3.0
    signac version    : 1.7.0
    flow version      : 0.21.0

    h5py version      : 3.7.0
    matplotlib version: 3.5.3
    numpy version     : 3.5.3
    pandas version    : 3.5.3
    pillow version    : 9.2.0
    scipy version     : 1.9.0
    sklearn version   : 1.1.2
    pyyaml version    : 6.0
    ** Serial CPU tests PASSED **

    + mpirun --npernode 1 singularity exec software.sif python3 mpi-cpu.py
    ** Starting MPI CPU tests **
    HOOMD version     : 3.4.0
    ** MPI CPU tests PASSED **
    + mpirun --npernode 1 singularity exec software.sif /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bw
    # OSU MPI Bandwidth Test v5.4.1
    # Size      Bandwidth (MB/s)
    1                       2.53
    2                       5.07
    4                      10.13
    8                      20.31
    16                     40.70
    32                     80.90
    64                    159.37
    128                   314.75
    256                   603.60
    512                  1186.74
    1024                 2437.16
    2048                 4385.84
    4096                 6576.44
    8192                10170.07
    16384               12811.31
    32768               15895.04
    65536               17412.40
    131072              18098.46
    262144              21474.57
    524288              22771.60
    1048576             22894.82
    2097152             22945.78
    4194304             23162.50
    + echo 'Tests complete.'
    Tests complete.
