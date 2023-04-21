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

Per OLCF policies, you should install your software in NFS under ``/ccs/proj/``. For example,
set the installation root directory to ``/ccs/proj/{your-project}/software/${USER}``.

Build the software environment and install it into the root::

    $ script/frontier/install.sh /ccs/proj/{your-project}/software/${USER}
    ... compiling software will take several minutes ...

Activate the environment with::

    $ source /ccs/proj/{your-project}/software/${USER}/environment.sh

The environment is a `python3 venv <https://docs.python.org/3/library/venv.html>`_. You may extend
it with additional python packages using ``python3 -m pip install``::

    $ source /ccs/proj/{your-project}/software/${USER}/environment.sh
    $ python3 -m pip install package

Use the following commands in your job scripts or interactively to execute software inside the
container::

    source /ccs/proj/{your-project}/software/${USER}/environment.sh
    srun {srun options} command arguments
