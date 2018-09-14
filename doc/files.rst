Accessing files
===============

Singularity's default behavior is very intuitive when it comes to accessing files on the host. If you have problems
accessing your files from within the container, read on to understand how the process works.

The container's filesystem
---------------------------

A container has its own filesystem baked into the image. The container's software is installed in it's filesystem.
Software executing inside the container will see different files than on the host. This starts
at the root of the filesystem::

    ▶ ls /
    bin   dev  home  lib64       mnt  opt   root  sbin  sys  usr
    boot  etc  lib   lost+found  nfs  proc  run   srv   tmp  var
    ▶ singularity exec software.simg ls /
    bin          etc               lib    mkdir  opt       run          srv  var
    boot         fresnel-examples  lib32  mnt    proc      sbin         sys
    dev          home              lib64  nfs    projects  scratch      tmp
    environment  hoomd-examples    media  oasis  root      singularity  usr

.. note::

    With Singularity, the container's filesystem is **read-only**.

Bind mounting
-------------

Specific directories may be *bind mounted* from the host into the container so it can access the contents directly. On most systems, Singularity is configured to bind mount your current working directory by default::

    ▶ echo "print('hello world')" > script.py
    ▶ singularity exec software.simg ls
    script.py  software.simg
    ▶ singularity exec software.simg python3 script.py
    hello world

Only specific directories are bind mounted. The above example was in ``testuser``'s home directory. Even though there
are many users on this host system, singularity only sees ``/glotzerlab-software`` (from the container image) and
``testuser`` (bind mounted) in ``/home``::

    ▶ singularity exec software.simg ls /home
    glotzerlab-software  testuser

.. tip::

    Most HPC systems also bind mount their scratch filesytems.

If you can't access files that you need to, make sure they are either in the current working directory at the time you
launch singularity, or they are on the scratch filesystem.

.. seealso::

    If this doesn't fit your workflow, see the
    `Singularity documentation <https://www.sylabs.io/docs/>`_ to learn how to specify your own bind mounts (if allowed by
    your system administrator).
