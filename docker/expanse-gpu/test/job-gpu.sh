#!/bin/bash
#SBATCH --job-name="test-gpu"
#SBATCH --partition=gpu
#SBATCH --nodes=1
#SBATCH --ntasks-per-node=2
#SBATCH --gpus=4
#SBATCH -t 0:10:00

module load gpu/0.15.4 singularitypro openmpi/4.0.4-nocuda

set -x

singularity exec software.sif bash -c "set" | grep GLOTZERLAB

singularity exec --nv software.sif python3 serial-gpu.py

mpirun -v singularity exec --nv software.sif python3 mpi-gpu.py

mpirun -v singularity exec software.sif /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

echo "Tests complete."
