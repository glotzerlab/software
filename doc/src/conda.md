# Conda packages

**glotzerlab-software** provides [conda] formatted packages built with cluster-specific
*MPI* and *CUDA* libraries. Use it to add *MPI-* and *GPU-enabled* builds of the
following software packages to your conda compatible environments on HPC resources:

-   hoomd
-   mpi4py

[conda]: https://docs.conda.io

> Important: These packages are built for ABI compatibility with packages on the
> **conda-forge** channel. Ensure that you have **no** packages installed
> from the **default** channel before proceeding.

[miniforge] provides a conda compatible environment pre-configured to install packages
only from **conda-forge**. When you install [miniforge] with default options, replace:

- `{{ package-manager }}` with `mamba`
- `{{ environment-path }}` with `$HOME/miniforge3`

[miniforge]: https://github.com/conda-forge/miniforge

If you are using a different conda compatible package manager, use the appropriate
`{{ package-manager }}` and `{{ environment-path }}`.

<div class="warning">
Do not install any <i>MPI</i> or <i>GPU</i> enabled packages from the <b>conda-forge</b>
channel. The generic <i>MPI</i> and <i>CUDA</i> libraries provided by
<b>conda-forge</b> will take precedence and prevent the cluster-specific libraries from
operating correctly.
</div>
