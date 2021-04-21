# Glotzerlab software

**glotzerlab-software** is a set of container images that provide software developed by the [Glotzer
group](<http://glotzerlab.engin.umich.edu>)_ at the [University of Michigan]
(https://www.umich.edu/) along with related software commonly used in simulation and data analysis
workflows.

## Resources

* [Documentation](https://glotzerlab-software.readthedocs.io/):
  Tutorial, usage information, and list of supported clusters.
* [hoomd-users Google Group](https://groups.google.com/d/forum/hoomd-users):
  Get support from the user community.
* [glotzerlab/software on Docker Hub](https://hub.docker.com/r/glotzerlab/software):
  See the list of published images.

## Quick start

First, download the stable **glotzerlab/software** image using
[Singularity](https://sylabs.io/singularity/)::

    $ singularity pull software.sif docker://glotzerlab/software

Or the beta (with HOOMD v3.0.0-beta)::

    $ singularity pull software.sif docker://glotzerlab/software:beta-nompi

**singularity exec** executes software from inside the container. For example, run a Python script
with::

    $ singularity exec software.sif python3 script.py

Add the ``--nv`` option to **enable NVIDIA GPUs** inside the container::

    $ singularity exec --nv software.sif nvidia-smi

## Updates

**glotzerlab-software** updates regularly with the latest versions of included software. Download
the latest image to update::

    $ singularity pull software.sif docker://glotzerlab/software

## Change log

See [CHANGELOG.rst](CHANGELOG.rst).

## Contributing

Contributions are welcomed via
[pull requests](https://github.com/glotzerlab/software/pulls).
Please report bugs and suggest feature enhancements via the
[issue tracker](https://github.com/glotzerlab/software/issues).
See [CONTRIBUTING.md](CONTRIBUTING.md) for more information.
