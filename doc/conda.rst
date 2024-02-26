Conda packages
==============

**glotzerlab-software** provides conda packages built with cluster-specific *MPI* and *CUDA*
libraries. Use it to add *MPI-* and *GPU-enabled* builds of **HOOMD-blue** and related
software to your conda environment on a HPC resource.

**glotzerlab-software** provides the following packages:

* hoomd
* mpi4py

.. danger::

    Do not install any MPI or GPU enabled packages from the **conda-forge** channel. The generic
    *MPI* and *CUDA* libraries provided by **conda-forge** will take precedence and prevent the
    cluster-specific libraries from operating correctly.

.. toctree::
    :maxdepth: 1

    glotzer
    build
    install
