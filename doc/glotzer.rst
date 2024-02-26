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

.. rubric:: Frontier

Individual users should install **miniforge** environments in their home directory (the default):
``$HOME/miniforge3`` on Frontier.

Importing Python packages from this environment will be *very* slow with large node count jobs.
To improve performance, generate a **tar** file from the environment and store it on Orion.

.. important::

    Repeat this step after you install or update packages with ``mamba``.

.. code-block::

    $ tar --directory $HOME/miniforge3 -cf ${MEMBERWORK}/mat110/miniforge3.tar .

.. tip::

    Collaborative projects should aim to install and maintain a single copy of the software.
    This should be installed to the project home::

        bash Miniforge3-Linux-x86_64.sh -b -p /ccs/proj/{your-project}/software/frontier/{subproject-name}
        chmod g+rwX /ccs/proj/{your-project}/software/frontier/{subproject-name} -R

    This allows environment changes to propagate between users, and cuts down on storage usage in
    the project home directory.

    Collaborative projects can also work off of a single cached ``miniforge3.tar``::

        $ tar --directory $HOME/miniforge3 -cf ${PROJWORK}/{your-project}/software/{subproject-name}/software.tar .

Use the following lines in your job scripts (or interactively with ``salloc``) to load the cache
into NVME and execute software from there::

    #SBATCH -C nvme

    module load PrgEnv-gnu rocm/5.4.3
    module unload darshan-runtime

    export MINIFORGE_ROOT=/mnt/bb/${USER}/miniforge
    srun --ntasks-per-node 1 mkdir ${MINIFORGE_ROOT}
    srun --ntasks-per-node 1 tar --directory ${MINIFORGE_ROOT} -xpf \
          ${MEMBERWORK}/mat110/miniforge3.tar
    #     ${PROJWORK}/{your-project}/software/{subproject-name}/miniforge3.tar # For use with shared projects.

    export PATH=${MINIFORGE_ROOT}/bin:$PATH

    srun {srun options} command arguments

.. note::

    The above script has been tested on environments with all packages installed into the base.
    You may need to set additional environment variables or source activation scripts to activate
    conda environments within this directory.
