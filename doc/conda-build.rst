Building packages
-----------------

If you are not a Glotzer Lab member, or would like to build these packages on a new resource:

1. Install ``conda-build`` and ``boa`` into your conda environment::

    mamba install conda-build boa

2. Obtain the **glotzerlab-software** source code::

    git clone https://github.com/glotzerlab/software

3. Change to the ``conda`` directory::

    cd software/conda

4. On Great Lakes, ANVIL, or Delta: Modify the ``output-folder`` in
   ``conda-build-<cluster>.sh`` and the account in ``job-build-all-<cluster>.sh``.
   Then submit ``job-build-all-<cluster>.sh`` to build the packages::

    sbatch job-build-all-<cluster>.sh

5. On a different HPC resource, use ``conda-build-greatlakes.sh`` as a starting point for your own
   build script. Modify the ``module load`` line, the cluster name (and device, if needed)
   ``--variants``, and the ``--output-folder``. Run the build script to build the packages::

    ./conda-build-<cluster>.sh hoomd mpi4py

.. important::

    The ``output-folder`` is the directory where ``conda build`` will write the packages. Set the
    channel path ``file://path/to/conda/channel`` in ``.condarc`` to the ``output-folder``.
