import matplotlib.pyplot as plt

num_nodes = 50

experiments = [
    ("rw_1walker", "1 Walker"),
    ("rw_2walkers", "2 Walkers"),
    ("rw_5walkers", "5 Walkers")
]

colors = ["#1f77b4", "#2ca02c", "#d62728"]

plt.figure(figsize=(10, 6))

for (folder, label), color in zip(experiments, colors):
    x, y, lbl = load_coverage_data(folder, num_nodes, label)
    plt.plot(x, y, label=lbl, linewidth=2.5, color=color)

# Style
plt.title("Random Walker Coverage Comparison", fontsize=14, weight='bold')
plt.xlabel("Hops", fontsize=12)
plt.ylabel("Coverage (%)", fontsize=12)
plt.ylim(0, 105)
plt.grid(True, linestyle='--', alpha=0.5)
plt.legend(title="Walker Count", fontsize=10, title_fontsize=11)
plt.tight_layout()

# Save and show
plt.savefig("walker_comparison.png", dpi=300)
plt.show()

def load_coverage_data(folder, num_nodes, label):
    import glob
    import numpy as np

    files = glob.glob(f"{folder}/unique_visited_nodes_run*.txt")
    data = []

    for fname in files:
        run = []
        with open(fname) as f:
            for line in f:
                timestep, visited = map(int, line.strip().split(","))
                run.append(visited)
        data.append(run)

    maxlen = max(len(run) for run in data)
    for run in data:
        if len(run) < maxlen:
            run += [num_nodes] * (maxlen - len(run))

    avg = np.mean(data, axis=0)
    percent_coverage = avg / num_nodes * 100
    timesteps = range(len(percent_coverage))

    return timesteps, percent_coverage, label

