
Change log
==========

**glotzerlab-software** releases update regularly. Releases are numbered by the year, month,
and optionally the day separated by periods or hyphens. The change log highlights major changes.
Find the complete archive of releases on `Docker Hub`_.

.. _Docker Hub: https://hub.docker.com/r/glotzerlab/software/tags

2024
----

2024-01-17
++++++++++

*Removed*

* Support for OLCF Summit.

2023
----

2023-10-27
++++++++++

*Added*

* Support Purdue Anvil.

2023-10-12
++++++++++

*Changed*

* Require openmpi/4.1.4 on Delta.
* Recommend ``export OMPI_MCA_btl=self`` and ``srun`` when launching MPI jobs on Delta.

2023-09-22
++++++++++

*Changed*

* Require openmpi/4.1.6 on Great Lakes.
* Set `PYTHONUBUFFERED=1`.


2022
----

2022-07-12
++++++++++

*Fixed*

* ``expanse-gpu`` execution with more than one MPI rank.

*Added*

* ``cupy`` Python package.

2022-07-11
++++++++++

*Added*

* ``delta`` image with support for NCSA Delta.

2021
----

2021-12-01
++++++++++

*Added*

* ``signac-dashboard`` Python package.

*Changed*

* Added ``expanse-gpu`` image with support for XSEDE Expanse's GPU nodes.

  * Expanse CPU jobs should use the ``expanse`` image and
    ``module load cpu singularitypro gcc/9.2.0 openmpi/4.1.1``.
  * GPU jobs should use the ``expanse-gpu`` image and
    ``module load gpu singularitypro openmpi/4.0.4``.

2021.11.09
++++++++++

*Changed*

* Use Ubuntu 20.04 base image.
* Use CUDA 11 base image.

*Removed*

* Stampede2 image.

2021.06.08
++++++++++

*Added:*

* Image for SDSC Expanse.

*Removed:*

* Image for SDSC Comet.

2021.04.21
++++++++++

*Added:*

* Environment variables that identify source commit and configuration of the image:
  ``GLOTZERLAB_SOFTWARE_GIT_SHA``, ``GLOTZERLAB_SOFTWARE_GIT_BRANCH``,
  ``GLOTZERLAB_SOFTWARE_CONFIGURATION``, and ``GLOTZERLAB_SOFTWARE_TAG``

*Changed:*

* New images are now pushed to Docker Hub on every commit to the mainline branches.
* Future change log entries will no longer document version bumps.

2021.03.24
++++++++++

*Changed:*

* ``glotzerlab-software`` images are no longer hosted at https://glotzerlab.engin.umich.edu.
  Use ``singularity pull software.sif docker://glotzerlab/software`` to download the image.

*Updated:*

* freud v2.5.0
* fresnel v0.13.1
* gsd v2.4.1
* libgetar v1.1.0

* HOOMD-blue

  * v2.9.6
  * Beta: v3.0.0-beta.5

* signac-flow v0.13.0

2021.02.25
++++++++++

*Updated:*

* Python 3.8
* HOOMD-blue

  * v2.9.4
  * Beta: v3.0.0-beta.4

2021.01.15
++++++++++

*Added:*

* Support PSC Bridges-2

*Updated:*

* freud v2.4.1
* rowan v1.3.0.post1
* signac v1.5.1
* HOOMD-blue

  * Beta: v3.0.0-beta.3

*Removed:*

* Support for PSC Bridges

2020
----

2020.12.15
++++++++++

*Updated:*

* HOOMD-blue

  * Beta: v3.0.0-beta.2


2020.11.18
++++++++++

*Updated:*

* coxeter v0.4.0
* freud v2.4.0
* garnett v0.7.1
* gsd v2.4.0
* signac v1.5.0
* signac-flow v0.11.0

2020.10
+++++++

*Updated:*

* gsd v2.2.0
* HOOMD-blue

  * Stable: v2.9.3
  * Beta: v3.0.0-beta.1

2020.07
+++++++

*Updated:*

* gsd v2.1.2
* HOOMD-blue v2.9.2

2020.04
+++++++

*Updated:*

* fresnel v0.12.0
* freud v2.2.0
* garnett v0.7.1
* gsd v2.1.1

*Changed:*

* Temporarily removed garnett: Ubuntu 18.04 does not provide a compatible
  ``numpy`` or ``tqdm``.

*Fixed:*

* Add python3-filelock

2020.02
+++++++

*Updated:*

* freud v2.1.0
* gsd v2.0.0
* HOOMD-blue v2.9.0
* signac v1.3.0
* signac-flow v0.9.0

2019
----

2019.12
+++++++

*Updated:*

* freud v2.0.1
* gsd v1.10.0
* HOOMD-blue v2.8.1

*Library/OS updates:*

* Ubuntu 18.04 and Python 3.6 now on all systems
* Great Lakes now requires ``module load openmpi/4.0.2``
* Bridges images are broken. Please use the ``nompi`` images on Bridges until
  we can resolve MPI support issues on Bridges.

2019.11
+++++++

*Updated:*

* fresnel v0.11.0
* freud v2.0.0
* garnett v0.6.1
* HOOMD-blue v2.8.0

*Library/OS updates:*

* Ubuntu 18.04 [not on comet]
* Python 3.6 [not on comet]

*Supported systems:*

* Removed UMich Flux


2019.10
+++++++

*Updated:*

* fresnel v0.10.1
* gsd v1.9.3
* HOOMD-blue v2.7.0
* rowan v1.2.2
* plato v1.7.0

2019.09
+++++++

*Updated:*

* fresnel v0.10.0
* freud v1.2.2
* garnett v0.5.0
* gsd v1.8.1
* signac-flow v0.8.0

*Library/OS updates:*

* embree v3.6.1
* [summit] TBB 2019_U8
* [summit] scipy v1.3.1
* [greatlakes] Ubuntu 18.04
* [greatlakes] Python 3.6

*Supported systems:*

* Added UMich Great Lakes

2019.08
+++++++

*New software:*

* garnett v0.4.1

*Updated:*

* freud v1.2.1
* gsd v1.8.0
* libgetar v1.0.1
* pythia v0.2.5
* siganc v1.2.0

2019.07
+++++++

*Updated:*

* freud v1.2.0
* HOOMD-blue v2.6.0
* rowan v1.2.1
* plato v1.6.0
* siganc v1.1.0

2019.05
+++++++

*Updated:*

* fresnel v0.9.0
* GSD v1.7.0
* HOOMD-blue v2.5.2
* signac-flow v0.7.1

2019.03
+++++++

*Updated:*

* fresnel v0.8.0
* freud v1.0.0
* GSD v1.6.1
* HOOMD-blue v2.5.1
* rowan v1.2.0
* signac v1.0.0

*Library updates:*

* embree 3.5.2

2019.02
+++++++

*Updated:*

* fresnel v0.7.1
* HOOMD-blue v2.5.0
* rowan v1.1.7
* signac v0.9.5
* [summit] scipy v1.2.0

*Library updates:*

* embree 3.4.0
* TBB 2019_U3

*Fixes:*

* Stampede2 multi-node MPI now works

2019.01
+++++++

*Updated:*

* gsd v1.6.0
* HOOMD-blue v2.4.2
* plato v1.4.0
* signac-flow v0.6.4

2018
----

2018.12
+++++++

*Updated:*

* Freud v0.11.4
* gsd v1.5.5
* HOOMD-blue v2.4.1
* plato v1.3.0
* pythia v0.2.4

*Supported systems:*

* Added Summit build scripts

2018.11
+++++++

*Updated:*

* Freud v0.11.3
* HOOMD-blue v2.4.0
* libgetar v0.7.0
* plato v1.2.0
* pythia v0.2.3
* rowan v1.1.6
* signac v0.9.4

2018.10
+++++++

*Updated:*

* Embree v3.2.1
* Freud v0.11.0
* GSD v1.5.4
* HOOMD-blue v2.3.5

2018.09
+++++++

*Changes:*

* Documentation now on readthedocs.org
* Latest images are now available directly from singularity-hub

*Updated:*

* Freud v0.10.0
* libgetar v0.6.1
* Rowan v1.1.0
* Signac-flow v0.6.3

2018.08
+++++++

*Updated:*

* Fresnel v0.6.0
* Freud v0.9.0
* HOOMD-blue v2.3.4

2018.07
+++++++

Added:

* pyhull

*Updated:*

* Freud v0.8.2
* HOOMD-blue v2.3.3
* Signac v0.9.3
* Signac-flow v0.6.1

2018.06
+++++++

Added:

* ffmpeg
* h5py
* jupyter
* mpi4py
* pandas
* pillow
* PyQt5
* pyyaml
* scipy
* scikit-learn
* libgetar v0.5.4
* Pythia v0.2.2
* Rowan v0.6.1
* Plato v1.1.0

*Updated:*

* Freud v0.8.1
* GSD v1.5.3
* HOOMD-blue v2.3.1
* Signac-flow v0.6.0

2018.04
+++++++

*Changes:*

* Tag MPI enabled builds for specific clusters
* Support SDSC Comet, PSC Bridges, TACC Stampede2, and University of Michigan Flux clusters.

*Updated:*

* Freud v0.8.0
* GSD v1.5.2
* HOOMD-blue v2.3.0

2018.03
+++++++

The initial release includes:

Glotzerlab software versions:

* Fresnel v0.5.0
* Freud v0.7.0
* GSD v1.5.1
* HOOMD-blue v2.2.4
* Signac v0.9.2
* Signac-flow v0.5.6

Commonly used tools:

* LLVM/clang
* python3
* matplotlib
* numpy
* pytest
* sphinx
