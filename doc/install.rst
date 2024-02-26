Installing packages
-------------------

1. `Install miniforge`_ (or your preferred conda environment provider).

2. `Configure condarc`_ to use the local HPC resource channel and **conda-forge**.

3. `Install packages`_::

    mamba install hoomd mpi4py

4. `Load prerequisite modules`_. For example::

    module load openmpi cuda

5. `Execute Python scripts`_. For example::

    srun -n 8 python3 script.py

.. _Install miniforge:

.. rubric:: Install miniforge.

Follow the `miniforge`_ installation instructions for your platform.
This document assumes that you installed to the default path ``$HOME/miniforge3``.

.. _miniforge: https://github.com/conda-forge/miniforge


.. _Configure condarc:

.. rubric:: Configure condarc.

Replace ``$HOME/miniforge3/.condarc`` with:

.. code::

    channel_priority: strict
    channels:
    - file://path/to/conda/channel
    - conda-forge

    disallow:
    - openmpi
    - mpich
    - cuda-cudart-dev

.. note::

    The ``disallow`` section prevents you from accidentally installing *MPI* and *GPU* packages
    from conda-forge.

.. _Install packages:

.. rubric:: Install packages

You should also install any non-MPI and non-GPU packages you need. For example::

    mamba install freud gsd


.. _Load prerequisite modules:

.. rubric:: Load prerequisite modules

Load the specific module versions that match those used to build the package.


.. _Execute Python scripts:

.. rubric:: Execute Python scripts

Use your HPC resource scheduler to execute scripts on the appropriate compute nodes. Use ``srun``,
``mpirun``, or the appropriate launcher for MPI execution.

.. tip::

    After initial installation and setup is complete, you can update packages to their latest
    versions with ``mamba update --all``.
