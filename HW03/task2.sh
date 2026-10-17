#!/bin/bash
#SBATCH --partition=instruction     # Needs a partition to work on! Euler doesn't have a default partition.
#SBATCH --ntasks=1                  # Single task
#SBATCH --cpus-per-task=20          # 20 CPU cores (the most threads we use)
#SBATCH --job-name=HW03_Q2          # Job name in queue
#SBATCH --output=%x.out             # stdout file, with job name
#SBATCH --error=%x.err              # stderr file, with job name
#SBATCH --time=0-00:10:00           # Time to run
#SBATCH --mem=4G

# Record the node's CPU layout (useful for the Q2c discussion)
echo "Node: $(hostname)"
lscpu | grep -E "Model name|Socket\(s\)|Core\(s\) per socket|Thread\(s\) per core"

# Program start
g++ task2.cpp convolution.cpp -Wall -O3 -std=c++17 -o task2 -fopenmp

# Start with an empty results file
> task2_times.txt

# n = 1024, t = 1, 2, ..., 20
for t in {1..20}; do
    out=$(./task2 1024 "$t")
    time_ms=$(echo "$out" | sed -n 3p)    # third line of output is the time in ms
    echo "$t $time_ms" >> task2_times.txt
    echo "t = $t:" $out
done
