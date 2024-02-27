Conda packages
==============

**glotzerlab-software** provides `conda`_ formatted packages built with cluster-specific *MPI* and
*CUDA* libraries. Use it to add *MPI-* and *GPU-enabled* builds of the following software packages
to your conda-compatible environments on HPC resources:

* hoomd
* mpi4py

.. important::

    These packages are built for ABI compatibility with packages on the **conda-forge** channel.
    Ensure that you have **no** packages installed from the **default** channel before proceeding.

.. tip::

    `miniforge`_ provides a conda-compatible environment pre-configured to install packages only
    from **conda-forge**. When you install `miniforge`_ with default options, replace:

    * ``{{ package-manager }}`` with ``mamba``
    * ``{{ environment-path }}`` with ``$HOME/miniforge3``

.. danger::

    Do not install any *MPI* or *GPU* enabled packages from the **conda-forge** channel. The generic
    *MPI* and *CUDA* libraries provided by **conda-forge** will take precedence and prevent the
    cluster-specific libraries from operating correctly.

.. toctree::
    :maxdepth: 1

    glotzer
    build
    install

.. _miniforge: https://github.com/conda-forge/miniforge

.. _conda: https://docs.conda.io
