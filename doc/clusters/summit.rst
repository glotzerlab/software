Summit (OLCF)
-------------

`Summit <https://www.olcf.ornl.gov/for-users/system-user-guides/summit/>`_ is massive supercomputer at ORNL with
6 NVIDIA V100 GPUs and 2 IBM Power9 CPUs per node. Apply for resources on Summit through the
`INCITE <http://www.doeleadershipcomputing.org/>`_,
`ALCC <https://science.energy.gov/ascr/facilities/accessing-ascr-facilities/alcc/>`_, or
`director's discretionary <https://www.olcf.ornl.gov/for-users/documents-forms/olcf-directors-discretion-project-application/#>`_
programs.

Summit does not support container execution at this time. **glotzerlab-software** instead provides a build script
and a module environment to create an equivalent software stack.

First, clone the **glotzerlab-software** repository::

    ▶ git clone https://bitbucket.org/glotzer/docker-glotzerlab-software
    ▶ cd docker-glotzerlab-software

If you already have a clone, update it::

    ▶ cd docker-glotzerlab-software
    ▶ git pull origin master

Per OLCF policies, you should install your software in NFS under ``/ccs/proj/``. Set the installation root directory to
``/ccs/proj/your-project/glotzerlab-software`` to share a single software installation with your project.
Include your username in the directory name (e.g. ``/ccs/proj/your-project/glotzerlab-software-$USER}``)
to install a user-specific set of software. The rest of this document will refer to this
root directory as ``${GLOTZERLAB_SOFTWARE_ROOT}``. You should replace this variable with the location you choose.

Build the software environment and install it into the root::

    ▶ script/summit/install.sh ${GLOTZERLAB_SOFTWARE_ROOT}
    ... compiling software will take several minutes ...

Activate the environment with::

    ▶ source ${GLOTZERLAB_SOFTWARE_ROOT}/environment.sh

The summit environment is intended to execute HOOMD simulations. Compared to the containerized environments,
the following packages are missing because they do not yet support the ppc64le architecture:

  * embree
  * fresnel

The following packages are missing because we have not yet tested these on summit:

  * clang/llvm
  * ffmpeg
  * libboost
  * h5py
  * matplotlib
  * pandas
  * pyqt5
  * scipy
  * sklearn
  * yaml

The summit environment is a `python3 venv <https://docs.python.org/3/library/venv.html>`_. You may extend it with
additional python packages using ``pip install``::

    ▶ source ${GLOTZERLAB_SOFTWARE_ROOT}/environment.sh

.. note::

    Not all python packages support the ppc64le architecture.

Use the following commands in your job scripts or interactively to execute software inside the container::

    source ${GLOTZERLAB_SOFTWARE_ROOT}/environment.sh
    jsrun <jsrun options> command arguments

.. note::

    Properly selecting jsrun options for your job is beyond the scope of this document. If you do not know how to
    choose these, seek expert help.
