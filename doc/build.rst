Building packages
-----------------

If you are not a Glotzer Lab member or would like to build these packages on a new resource:

1. Install ``conda-build`` and ``boa`` into your conda environment::

    mamba install conda-build boa

2. Obtain the **glotzerlab-software** source code::

    git clone https://github.com/glotzerlab/software

3. Change to the ``conda`` directory::

    cd software/conda

4. Load any modules needed to provide compilers, MPI, and CUDA (optional). For example::

    module load gcc openmpi cuda

5. Build the packages::

    ./build.sh hoomd mpi4py \
        --skip-existing \
        --variants "{'cluster': ['<cluster name>'], 'device': ['gpu'], 'gpu_platform': ['CUDA']}" \
        --output-folder /path/to/conda/channel

.. important::

    The ``output-folder`` is the directory where ``conda build`` will write the packages. Set the
    channel path ``file://path/to/conda/channel`` in ``.condarc`` to match the ``output-folder``.
