Building packages
-----------------

If you are not a Glotzer Lab member or you would like to build these packages on a new resource:

.. note::

    Replace ``{{ package-manager }}`` with the name of your preferred conda-compatible package manager
    executable.

1. Install ``conda-build`` and ``boa`` into your environment::

    {{ package-manager }} install conda-build boa

2. Obtain the **glotzerlab-software** source code::

    git clone https://github.com/glotzerlab/software

3. Change to the ``conda`` directory::

    cd software/conda

4. Load any modules needed to provide compilers, *MPI*, and *CUDA* (optional). For example::

    module load gcc openmpi cuda

5. Build the packages::

    ./build.sh hoomd mpi4py \
        --skip-existing \
        --variants "{'cluster': ['{{ cluster-name }}'], 'device': ['gpu'], 'gpu_platform': ['CUDA']}" \
        --output-folder {{ channel-path }}

.. important::

    The ``output-folder`` is the directory where ``conda build`` will write the packages. Set the
    channel path ``file:/{{ channel-path }}`` in ``.condarc`` to match (see :doc:`install`).
