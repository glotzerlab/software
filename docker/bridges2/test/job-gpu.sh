#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=GPU
#SBATCH --nodes=2
#SBATCH --gpus-per-node=8
#SBATCH --ntasks-per-node=1
#SBATCH -t 0:10:00

module load openmpi/4.0.5-gcc10.2.0

set -x

singularity exec software.sif bash -c "set" | grep GLOTZERLAB

mpirun -v -n 1 singularity exec --nv software.sif python3 serial-gpu.py

mpirun -v singularity exec --nv software.sif python3 mpi-gpu.py

mpirun -v singularity exec software.sif /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

echo "Tests complete."
