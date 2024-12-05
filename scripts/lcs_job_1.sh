#!/bin/bash
#
#SBATCH --cpus-per-task=1
#SBATCH --nodes=1
#SBATCH --ntasks=4
#SBATCH --partition=slow
#SBATCH --mem=10G

srun ./lcs_distributed --inputFile=input_files/text.txt