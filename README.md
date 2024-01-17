# Glotzerlab software

**glotzerlab-software** is a set of container images that provide software developed by the [Glotzer
group](<http://glotzerlab.engin.umich.edu>) at the [University of Michigan](https://www.umich.edu/)
along with related software commonly used in simulation and data analysis workflows.

## Resources

* [Documentation](https://glotzerlab-software.readthedocs.io/):
  Tutorial, usage information, and list of supported clusters.
* [glotzerlab-software discussion board](https://github.com/glotzerlab/software/discussions):
  Ask the **glotzerlab-software** user community for help.
* [glotzerlab/software on Docker Hub](https://hub.docker.com/r/glotzerlab/software):
  See the list of published images.

## Quick start

First, download the stable **glotzerlab/software** image using
[Singularity](https://sylabs.io/singularity/):

    $ singularity pull software.sif docker://glotzerlab/software

**singularity exec** executes software from inside the container. For example, run a Python script
with:

    $ singularity exec software.sif python3 script.py

Add the ``--nv`` option to **enable NVIDIA GPUs** inside the container:

    $ singularity exec --nv software.sif nvidia-smi

## Updates

**glotzerlab-software** updates regularly with the latest versions of included software. Download
the latest image to update:

    $ singularity pull software.sif docker://glotzerlab/software

## Change log

See [CHANGELOG.rst](CHANGELOG.rst).

## Contributing

Contributions are welcomed via
[pull requests](https://github.com/glotzerlab/software/pulls).
Please report bugs and suggest feature enhancements via the
[issue tracker](https://github.com/glotzerlab/software/issues).
See [ARCHITECTURE.md](ARCHITECTURE.md) for information on how the repository is structured,
including how to modify the containers.
