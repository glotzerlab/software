Glotzerlab software images
++++++++++++++++++++++++++

**glotzerlab-software** deploys software developed by the `Glotzer group
<http://glotzerlab.engin.umich.edu>`_ at the `University of Michigan <https://www.umich.edu/>`_ to
HPC resources via conda packages and container images. Use **glotzerlab-software** to install a MPI
and GPU enabled build of HOOMD-blue on a *HPC resource*. Use the standard **conda-forge** provided
HOOMD-blue (``mamba install hoomd`` with no special configuration) for serial execution on individual
workstations.

.. note::

    Use conda packages for new installations. The container images are deprecated and will no longer
    be maintained after 2024-06-01.

.. toctree::
    :maxdepth: 1

    conda
    container
    changes
    license
