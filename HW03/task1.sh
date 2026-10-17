#!/bin/bash
#SBATCH --partition=instruction     # Needs a partition to work on! Euler doesn't have a default partition.
#SBATCH --ntasks=1                  # Single task
#SBATCH --cpus-per-task=20          # 20 CPU cores (the most threads we use)
#SBATCH --job-name=HW03_Q1          # Job name in queue
#SBATCH --output=%x.out             # stdout file, with job name
#SBATCH --error=%x.err              # stderr file, with job name
#SBATCH --time=0-00:10:00           # Time to run
#SBATCH --mem=4G

# Program start
g++ task1.cpp matmul.cpp -Wall -O3 -std=c++17 -o task1 -fopenmp

# Start with an empty results file
> task1_times.txt

# n = 1024, t = 1, 2, ..., 20
for t in {1..20}; do
    out=$(./task1 1024 "$t")
    time_ms=$(echo "$out" | sed -n 3p)    # third line of output is the time in ms
    echo "$t $time_ms" >> task1_times.txt
    echo "t = $t:" $out
done
