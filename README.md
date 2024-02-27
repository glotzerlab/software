# Glotzerlab software

**glotzerlab-software** deploys software developed by the [Glotzer
group](<http://glotzerlab.engin.umich.edu>) at the [University of Michigan](https://www.umich.edu/)
to HPC resources via conda packages and container images. Use **glotzerlab-software** to install
a MPI and GPU enabled build of HOOMD-blue on a *HPC resource*. Use the standard conda-forge
provided HOOMD-blue (`mamba install hoomd` with no special configuration) for serial execution
on individual workstations.

## Resources

* [Documentation](https://glotzerlab-software.readthedocs.io/):
  Tutorial, usage information, and list of supported HPC resources.
* [glotzerlab-software discussion board](https://github.com/glotzerlab/software/discussions):
  Ask the **glotzerlab-software** user community for help.
* [HOOMD-blue](https://glotzerlab.engin.umich.edu/hoomd-blue/): The general-purpose particle
  simulation toolkit that **glotzerlab-software** packages.

## Quick start [conda]

1. Install [miniforge](https://github.com/conda-forge/miniforge).
2. Replace `$HOME/miniforge3/.condarc` with:

       channel_priority: strict
       channels:
         - file://path/to/conda/channel
         - conda-forge

       disallow:
       - openmpi
       - mpich
       - cuda-cudart-dev

3. Install HOOMD-blue:

       mamba install hoomd

4. Load prerequisite modules. For example:

       module load openmpi cuda

5. Execute Python scripts with MPI and GPU support. For example:

       srun -n 8 python3 script.py

You can confirm that the correct package was installed with `mamba list hoomd`. The full package
build will contain the cluster name and a `gpu` or `cpu` suffix. For example:

    # Name      Version   Build                          Channel
    hoomd       X.Y.Z     cluster_gpu_py311h1b32822_0    file://path/to/conda/channel

## Quick start [container]

Download the stable **glotzerlab/software** image using
[Singularity](https://sylabs.io/singularity/):

    $ singularity pull software.sif docker://glotzerlab/software

**singularity exec** executes software from inside the container. For example, run a Python script
with:

    $ singularity exec software.sif python3 script.py

Add the ``--nv`` option to **enable NVIDIA GPUs** inside the container:

    $ singularity exec --nv software.sif nvidia-smi

**glotzerlab-software** updates regularly with the latest versions of included software. Download
the latest image to update:

    $ singularity pull software.sif docker://glotzerlab/software

## Change log

See [CHANGELOG.rst](CHANGELOG.rst).

## Contributing

Contributions are welcomed via [pull requests](https://github.com/glotzerlab/software/pulls). Please
report bugs and suggest feature enhancements via the [issue
tracker](https://github.com/glotzerlab/software/issues). See [ARCHITECTURE.md](ARCHITECTURE.md) for
information on how the repository is structured, including how to modify the containers.
