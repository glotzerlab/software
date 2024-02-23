Profiling
---------

You can run profiling tools to determine what operations take time while running executables within
the container. Some profiling tools must be executed on the host as they use tight integrations with
the Linux kernel.

GPU
***

Use ``nvprof`` with the option ``--profile-child-processes``::

    $ nvprof --profile-child-processes singularity exec --nv software.sif python3 lj.py

On platforms where you need to launch HOOMD with MPI, call ``nvprof`` after ``mpirun``::

    $ mpirun -n 1 nvprof --profile-child-processes \
      singularity exec --nv software.sif.sif python3 lj.py

.. note::

    You may need to add the ``nvprof`` option ``--openacc-profiling off`` on some systems.

CPU
***

Build HOOMD from source to profile it on the CPU.  The CPU profiler `perf` does not interoperate
with Singularity containers.
