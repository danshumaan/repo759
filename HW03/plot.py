import os

import matplotlib
matplotlib.use("Agg")  # draw straight to a file, no screen needed
import matplotlib.pyplot as plt
import numpy as np


def plot_vs_threads(times_file, pdf_file, title):
    # Each line of times_file is: t time_ms
    data = np.loadtxt(times_file)
    t = data[:, 0]
    time_ms = data[:, 1]

    plt.figure(figsize=(7, 5))
    plt.plot(t, time_ms, marker="o")
    plt.xticks(range(1, 21))
    plt.ylim(bottom=0)
    plt.xlabel("t (number of threads)")
    plt.ylabel("Time (ms)")
    plt.title(title)
    plt.grid(True, linestyle="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig(pdf_file)
    plt.close()
    print("Made", pdf_file)


def plot_vs_threshold(times_file, pdf_file, title):
    # Each line of times_file is: ts time_ms
    data = np.loadtxt(times_file)
    ts = data[:, 0]
    time_ms = data[:, 1]

    plt.figure(figsize=(7, 5))
    plt.plot(ts, time_ms, marker="o")
    plt.xscale("log", base=2)  # linear-log: log x axis, linear y axis
    plt.xticks(ts, [f"$2^{{{int(np.log2(v))}}}$" for v in ts])  # label every power of 2
    plt.minorticks_off()
    plt.ylim(bottom=0)
    plt.xlabel("ts (threshold)")
    plt.ylabel("Time (ms)")
    plt.title(title)
    plt.grid(True, which="both", linestyle="--", alpha=0.5)
    plt.tight_layout()
    plt.savefig(pdf_file)
    plt.close()
    print("Made", pdf_file)


# Make every plot whose times file is present
if os.path.exists("task1_times.txt"):
    plot_vs_threads("task1_times.txt", "task1.pdf", "Q1c. Parallel mmul, n = 1024")

if os.path.exists("task2_times.txt"):
    plot_vs_threads("task2_times.txt", "task2.pdf", "Q2c. Parallel convolve, n = 1024, 3x3 mask")

if os.path.exists("task3_ts_times.txt"):
    plot_vs_threshold("task3_ts_times.txt", "task3_ts.pdf", "Q3c. Parallel msort, n = $10^6$, t = 8")

if os.path.exists("task3_t_times.txt"):
    with open("task3_t_times.txt") as f:
        ts_used = f.readline().strip("# \n")  # first line looks like "# ts = 64"
    plot_vs_threads("task3_t_times.txt", "task3_t.pdf", f"Q3c. Parallel msort, n = $10^6$, {ts_used}")
