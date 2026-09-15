#!/bin/bash
#SBATCH --partition=instruction     # Needs a partition to work on! Euler doesn't have a default partition.
#SBATCH --ntasks=1                  # Single task
#SBATCH --cpus-per-task=2           # 2 CPU cores
#SBATCH --job-name=FirstSlurm       # Job name in queue
#SBATCH --output=%x.out             # stdout file, with job name
#SBATCH --error=%x.err              # stderr file, with job name
#SBATCH --time=0-00:01:00           # Time to run

# Program start
hostname