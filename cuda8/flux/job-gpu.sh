#!/bin/bash
#PBS -N test_gpu
#PBS -A sglotzer1_fluxoe
#PBS -l nodes=1:gpus=1,walltime=00:10:00
#PBS -l qos=flux
#PBS -q fluxoe
#PBS -j oe

# change to the job submission directory
cd ${PBS_O_WORKDIR}

module load gcc/5.4.0
module load openmpi/3.0.0/gcc/5.4.0

module load singularity

rm -f test-results-gpu.out

singularity exec --nv software.simg python3 serial-gpu.py

