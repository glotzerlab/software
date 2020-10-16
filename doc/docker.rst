Docker
======

**glotzerlab-software** is available on the `Docker Hub
<https://hub.docker.com/r/glotzerlab/software/>`_ for use on docker based systems (for example:
cloud platforms).

You can start an interactive session of the glotzerlab/software image with the following command::

    $ docker run --rm -it glotzerlab/software
    Python 3.6.9 (default, Oct  8 2020, 12:12:24)
    [GCC 8.4.0] on linux
    Type "help", "copyright", "credits" or "license" for more information.
    >>> import hoomd
    >>> import freud
    >>> import signac

You can utilize NVIDIA GPUs on local and cloud systems with the NVIDIA container runtime. See the
`NVIDIA GPU CLOUD documentation <http://docs.nvidia.com/ngc/index.html#ngc-with-nvidia-titan-pcs>`_
for more information::

    $ docker run --gpus=device=all --rm -it glotzerlab/software
    glotzerlab-software@b0cbab541230:/$ nvidia-smi
    +-----------------------------------------------------------------------------+
    | NVIDIA-SMI 450.57       Driver Version: 450.57       CUDA Version: 11.0     |
    |-------------------------------+----------------------+----------------------+
    | GPU  Name        Persistence-M| Bus-Id        Disp.A | Volatile Uncorr. ECC |
    | Fan  Temp  Perf  Pwr:Usage/Cap|         Memory-Usage | GPU-Util  Compute M. |
    |                               |                      |               MIG M. |
    |===============================+======================+======================|
    |   0  Quadro RTX 5000     On   | 00000000:02:00.0 Off |                  Off |
    | 33%   29C    P8    16W / 230W |      1MiB / 16124MiB |      0%      Default |
    |                               |                      |                  N/A |
    +-------------------------------+----------------------+----------------------+

Tutorials on accessing files, executing parallel jobs, and extending docker images are beyond the
scope of this documentation.

.. seealso::

    The `Docker documentation <https://docs.docker.com/>`_ and the documentation for the docker
    based platform you are using.
