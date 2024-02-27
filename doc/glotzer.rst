Glotzer lab members
-------------------

Members of the Glotzer lab can install precompiled packages. Follow the instructions in
:doc:`install` to install the latest stable release using the following channel paths and module
versions:

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

Individual users should install conda-compatible environments in their **home directory** on
Frontier. Importing Python packages from this environment will be *very* slow with large node count
jobs. To improve performance, generate a **tar** file from the environment and store it on Orion.

.. important::

    Repeat this step after you install or update packages with ``{{ package-manager }}``.

.. code-block::

    $ tar --directory {{ environment-path }} -cf ${MEMBERWORK}/mat110/conda-env.tar .

.. tip::

    Collaborative projects may maintain a single copy of the software in the shared project
    directory: ``/ccs/proj/mat110/software/frontier/{{ subproject-name }}``.

    Collaborative projects may also utilize a single cached ``conda-env.tar``::

        $ tar --directory /ccs/proj/mat110/software/frontier/{{ subproject-name }} \
          -cf ${PROJWORK}/mat110/software/{{ subproject-name} }/conda-env.tar .

Use the following lines in your job scripts (or interactively with ``salloc``) to load the
environment into NVME and execute software from there::

    #SBATCH -C nvme

    module load PrgEnv-gnu rocm/5.4.3
    module unload darshan-runtime

    export CONDA_ENV_ROOT=/mnt/bb/${USER}/conda-env
    srun --ntasks-per-node 1 mkdir ${CONDA_ENV_ROOT}
    srun --ntasks-per-node 1 tar --directory ${CONDA_ENV_ROOT} -xpf \
          ${MEMBERWORK}/mat110/conda-env.tar
    #     ${PROJWORK}/mat110/software/{{ subproject-name }}/conda-env.tar # For use with shared projects.

    export PATH=${CONDA_ENV_ROOT}/bin:$PATH

    srun {srun options} command arguments

.. note::

    The above script has been tested on environments with all packages installed into *base*.
    You may need to set additional environment variables or source activation scripts to activate
    conda environments within this directory.
