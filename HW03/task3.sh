#!/bin/bash
#SBATCH --partition=instruction     # Needs a partition to work on! Euler doesn't have a default partition.
#SBATCH --ntasks=1                  # Single task
#SBATCH --cpus-per-task=20          # 20 CPU cores (the most threads we use)
#SBATCH --job-name=HW03_Q3          # Job name in queue
#SBATCH --output=%x.out             # stdout file, with job name
#SBATCH --error=%x.err              # stderr file, with job name
#SBATCH --time=0-00:15:00           # Time to run
#SBATCH --mem=4G

# Program start
g++ task3.cpp msort.cpp -Wall -O3 -std=c++17 -o task3 -fopenmp

n=1000000

# Part 1: n = 10^6, t = 8, ts = 2^1, 2^2, ..., 2^10
> task3_ts_times.txt
for i in {1..10}; do
    ts=$((2**i))
    out=$(./task3 "$n" 8 "$ts")
    time_ms=$(echo "$out" | sed -n 3p)    # third line of output is the time in ms
    echo "$ts $time_ms" >> task3_ts_times.txt
    echo "ts = 2^$i = $ts:" $out
done

# The ts with the smallest time in part 1
best_ts=$(sort -g -k2 task3_ts_times.txt | head -n 1 | cut -d ' ' -f 1)
echo "Best ts = $best_ts"

# Part 2: n = 10^6, ts = best ts, t = 1, 2, ..., 20
# The first line records which ts was used (plot.py puts it in the title)
echo "# ts = $best_ts" > task3_t_times.txt
for t in {1..20}; do
    out=$(./task3 "$n" "$t" "$best_ts")
    time_ms=$(echo "$out" | sed -n 3p)
    echo "$t $time_ms" >> task3_t_times.txt
    echo "t = $t:" $out
done
