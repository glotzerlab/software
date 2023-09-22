#!/bin/bash
#SBATCH --job-name="test-cpu"
#SBATCH --partition=standard
#SBATCH --nodes=2
#SBATCH --ntasks=2
#SBATCH --cpus-per-task=1
#SBATCH --export=ALL
#SBATCH -t 0:10:00

export PMIX_MCA_psec=^munge

module load gcc/10.3.0 openmpi/4.1.6 singularity

set -x
cd $SLURM_SUBMIT_DIR

mpirun -n 1 singularity exec --bind /scratch,/gpfs software.sif python3 serial-cpu.py

mpirun singularity exec --bind /scratch,/gpfs software.sif python3 mpi-cpu.py

mpirun singularity exec --bind /scratch,/gpfs software.sif /opt/osu-micro-benchmarks/libexec/osu-micro-benchmarks/mpi/pt2pt/osu_bibw

echo "Tests complete."
