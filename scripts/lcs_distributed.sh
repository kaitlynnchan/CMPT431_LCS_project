#!/bin/bash
#
#SBATCH --cpus-per-task=1
#SBATCH --nodes=1
#SBATCH --ntasks=2
#SBATCH --partition=slow
#SBATCH --mem=10G
#SBATCH --output="output_files/slurm_output_distributed"

srun ./lcs_distributed --inputFile=input_files/input_size1000.txt
