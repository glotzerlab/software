Frontier (OLCF)
---------------

`frontier <https://docs.olcf.ornl.gov/systems/frontier_user_guide.html>`_ is a system
at ORNL.

Frontier does not support container execution at this time. **glotzerlab-software** instead provides
a build script and a module environment to create an equivalent software stack.

First, clone the **glotzerlab-software** repository::

    $ git clone https://github.com/glotzerlab/software
    $ cd software

If you already have a clone, update it::

    $ cd software
    $ git pull origin trunk

You should install your software in NFS under ``/ccs/proj/``. For example,
set the installation root directory to ``/ccs/proj/{your-project}/software/frontier/${USER}``.

Build the software environment and install it into the root::

    $ script/frontier/install.sh /ccs/proj/{your-project}/software/frontier/${USER}
    ... compiling software will take several minutes ...

Activate the environment with::

    $ source /ccs/proj/{your-project}/software/frontier/${USER}/environment.sh

The environment is a `python3 venv <https://docs.python.org/3/library/venv.html>`_. You may extend
it with additional python packages using ``python3 -m pip install``::

    $ source /ccs/proj/{your-project}/software/frontier/${USER}/environment.sh
    $ python3 -m pip install package

Importing Python packages from this environment will be *very* slow with large node count jobs.
To improve performance, generate a tar file with the environment and store it on Orion (repeat this
step after you update the environment or install packages with ``pip``)::

    $ /ccs/proj/{your-project}/software/frontier/${USER}/generate-tar-cache.sh \
      ${MEMBERWORK}/{your-project}/software.tar

Use the following commands in your job scripts (or interactively with ``salloc``) to load the cache
into NVME and execute software from there::

    #SBATCH -C nvme

    export GLOTZERLAB_SOFTWARE_ROOT=/mnt/bb/${USER}/software
    srun --ntasks-per-node 1 mkdir ${GLOTZERLAB_SOFTWARE_ROOT}
    srun --ntasks-per-node 1 tar --directory ${GLOTZERLAB_SOFTWARE_ROOT} -xpf \
      ${MEMBERWORK}/{your-project}/software.tar

    source ${GLOTZERLAB_SOFTWARE_ROOT}/variables.sh
    srun {srun options} command arguments
