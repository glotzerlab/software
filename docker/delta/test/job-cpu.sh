#!/bin/bash
#SBATCH --job-name="test-cpu"
#SBATCH --partition=cpu
#SBATCH --nodes=2
#SBATCH --ntasks-per-node=1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

module load gcc/11.2.0 openmpi/4.1.4

set -x

export OMPI_MCA_btl=self

singularity exec software.sif bash -c "set" | grep GLOTZERLAB

srun -n 1 singularity exec software.sif python3 serial-cpu.py

srun singularity exec software.sif python3 mpi-cpu.py

srun singularity exec software.sif /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

echo "Tests complete."
