Docker
======

**glotzerlab-software** is available on the `Docker Hub <https://hub.docker.com/r/glotzerlab/software/>`_ for use on
docker based systems (for example: cloud platforms).

You can start an interactive session of the glotzerlab/software image with the following command::

    ▶ docker run --rm -it glotzerlab/software
    glotzerlab-software@2f06ae2f7ce0:/$ python3
    Python 3.5.2 (default, Nov 23 2017, 16:37:01)
    [GCC 5.4.0 20160609] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import hoomd
    >>> import freud
    >>> import signac

You can utilize NVIDIA GPUs on local and cloud systems with the NVIDIA container runtime. See the
`NVIDIA GPU CLOUD documentation <http://docs.nvidia.com/ngc/index.html#ngc-with-nvidia-titan-pcs>`_ for more
information::

    ▶ docker run --runtime=nvidia --rm -it glotzerlab/software
    glotzerlab-software@b0cbab541230:/$ nvidia-smi
    Fri Sep 14 15:51:34 2018
    +-----------------------------------------------------------------------------+
    | NVIDIA-SMI 396.54                 Driver Version: 396.54                    |
    |-------------------------------+----------------------+----------------------+
    | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
    |===============================+======================+======================|
    |   0  Quadro GP100        On   | 00000000:03:00.0 Off |                  Off |
    | 33%   50C    P0    37W / 235W |      2MiB / 16278MiB |      0%      Default |
    +-------------------------------+----------------------+----------------------+

Tutorials on accessing files, executing parallel jobs, and extending docker images are beyond the scope of this
documentation.

.. seealso::

    The `Docker documentation <https://docs.docker.com/>`_ and the documentation for the docker based platform you
    are using.
