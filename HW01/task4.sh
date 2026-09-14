#!/bin/bash
#SBATCH --job-name=FirstSlurm       # Job name in queue
#SBATCH --output=%x.out             # stdout file, with job name
#SBATCH --error=%x.err              # stderr file, with job name

# Program start
hostname