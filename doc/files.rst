Accessing files
----------------

The container's filesystem
**************************

A container has its own filesystem baked into the image. The container's software is installed in
it's filesystem. Software executing inside the container will see different files than on the host.
This starts at the root of the filesystem::

    $ ls /
    bin   dev  home  lib64       mnt  opt   root  sbin  sys  usr
    boot  etc  lib   lost+found  nfs  proc  run   srv   tmp  var
    $ singularity exec software.sif ls /
    bin          etc               lib    mkdir  opt       run          srv  var
    boot         fresnel-examples  lib32  mnt    proc      sbin         sys
    dev          home              lib64  nfs    projects  scratch      tmp
    environment  hoomd-examples    media  oasis  root      singularity  usr

.. note::

    With Singularity, the container's filesystem is **read-only**.

Bind mounting
*************

Specific directories may be *bind mounted* from the host into the container so it can access the
contents directly. On most systems, Singularity is configured to bind mount your home directory by
default::

    $ echo "print('hello world')" > script.py
    $ singularity exec software.sif ls
    script.py  software.sif
    $ singularity exec software.sif python3 script.py
    hello world

Only specific directories are bind mounted. The above example was in ``testuser``'s home directory.
Even though there are many users on this host system, singularity only sees ``/glotzerlab-software``
(from the container image) and ``testuser`` (bind mounted) in ``/home``::

    $ singularity exec software.sif ls /home
    glotzerlab-software  testuser

You can bind mount additional directories with the ``--bind`` command line option.

.. tip::

    Bind the scratch filesystems when launching singularity processes on HPC systems. For example::

        singularity exec --nv --bind /scratch

.. seealso::

    If this doesn't fit your workflow, see the `Singularity documentation
    <https://www.sylabs.io/docs/>`_ to learn how to specify your own bind mounts (if allowed by your
    system administrator).
