Glotzer lab members
-------------------

Members of the Glotzer lab: Follow the instructions in :doc:`install` to install the latest stable
release using the following channel paths and module versions:

.. list-table::
    :header-rows: 1

    * - HPC resource
      - Channel location
      - Module versions
    * - UMich Great Lakes:
      - ``file://nfs/turbo/glotzer/software/conda``
      - .. code::

            module load gcc/10.3.0 openmpi/4.1.6 cuda/12.3.0
    * - Purdue ANVIL:
      - ``file://anvil/projects/x-dmr140129/software/conda``
      - .. code::

            module load gcc/11.2.0 openmpi/4.1.6
    * - NCSA Delta:
      - ``file://projects/bbgw/software/conda``
      - .. code::

            module load gcc/11.4.0 openmpi/4.1.6 cuda/12.3.0
    * - OLCF Frontier:
      - ``file://ccs/proj/mat110/software/frontier/conda``
      - .. code::

            module load PrgEnv-gnu rocm/5.4.3
            module unload darshan-runtime

    * - OLCF Andes:
      - ``file://ccs/proj/mat110/software/andes/conda``
      - .. code::

            module load gcc/10.3.0 openmpi/4.1.2
