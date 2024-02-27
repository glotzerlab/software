Installing packages
-------------------

1. **Configure condarc** to use the local HPC resource channel and **conda-forge**.

   Replace ``{{ environment-path }}/.condarc`` with:

   .. code::

       channel_priority: strict
       channels:
       - file:/{{ channel-path }}
       - conda-forge
       disallow:
       - openmpi
       - mpich
       - cuda-cudart-dev

   and keep any custom configuration options you would like.

   .. note::
       The ``disallow`` section prevents you from accidentally installing *MPI* and *GPU* packages
       from conda-forge.

2. **Install the packages**::

    {{ package-manager }} install hoomd mpi4py

3. **Load the module versions** that match those used to build the package. For example::

    module load openmpi/X.Y.Z cuda/I.J.K

4. **Execute Python scripts**. Use your HPC resource scheduler to request compute nodes and use the
   resources's MPI launcher. For example::

    srun -n 8 python3 script.py

.. tip::

    After initial installation and setup is complete, you can update packages to their latest
    versions with ``{{package-manager}} update --all``.
