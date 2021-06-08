Tests
============

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

After the jobs complete, examine the test output::

    $ cat test-results-cpu.out
    ** Starting serial CPU tests **
    Fresnel version   : 0.6.0
    Fresnel device    : <fresnel.Device: All available CPU threads>
    Freud version     : 0.10.0
    GSD version       : 1.5.3
    HOOMD version     : 2.3.4
    HOOMD flags       : CUDA (8.0) DOUBLE HPMC_MIXED MPI TBB SSE SSE2 SSE3 SSE4_1 SSE4_2 AVX AVX2
    libgetar version  : 0.6.1
    pythia version    : 0.2.2
    plato version     : 1.1.0
    rowan version     : 1.1.0
    signac version    : 0.9.3
    flow version      : 0.6.3

    h5py version      : 2.6.0
    matplotlib version: 1.5.1
    numpy version     : 1.5.1
    pandas version    : 1.5.1
    pillow version    : 5.2.0
    pyhull version    : 2015.2.0
    scipy version     : 0.17.0
    sklearn version   : 0.17
    pyyaml version    : 3.11
    ** Serial CPU tests PASSED **

    ** Starting MPI CPU tests **
    HOOMD version     : 2.3.4
    ** MPI CPU tests PASSED **
    # OSU MPI Bi-Directional Bandwidth Test v5.4.1
    # Size      Bandwidth (MB/s)
    1                       0.02
    2                       0.03
    4                       0.07
    8                       0.18
    16                      0.27
    32                      0.59
    64                      0.93
    128                   137.51
    256                   270.04
    512                   520.99
    1024                  999.65
    2048                 1818.69
    4096                 3349.42
    8192                 5120.30
    16384                  37.72
    32768                  90.25
    65536                 159.50
    131072                579.37
    262144               1547.74
    524288               3464.45
    1048576              7672.50
    2097152              7377.73
    4194304              7640.81

    $ cat test-results-gpu.out
    ** Starting serial GPU tests **
    HOOMD version     : 2.3.4
    HOOMD flags       : CUDA (8.0) DOUBLE HPMC_MIXED MPI TBB SSE SSE2 SSE3 SSE4_1 SSE4_2 AVX AVX2
    ** Serial GPU tests PASSED **
