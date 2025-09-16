from coverage_utils import load_coverage_data
import matplotlib.pyplot as plt

num_nodes = 50
experiments = [
    ("rw_1", "1 Walker"),
    ("rw_2", "2 Walkers"),
    ("rw_5", "5 Walkers")
]
colors = ["#1f77b4", "#2ca02c", "#d62728"]

plt.figure(figsize=(10, 6))

for (folder, label), color in zip(experiments, colors):
    x, y = load_coverage_data(folder, num_nodes, label)
    plt.plot(x, y, label=label, linewidth=2.5, color=color)

plt.title("Random Walker Network Coverage (Up to 99.5%)", fontsize=14, weight='bold')
plt.xlabel("Hops", fontsize=12)
plt.ylabel("Coverage (%)", fontsize=12)
plt.ylim(0, 105)
plt.grid(True, linestyle='--', alpha=0.5)
plt.legend(title="Walker Count", fontsize=10, title_fontsize=11)
plt.tight_layout()
plt.savefig("walker_comparison.png", dpi=300)
plt.show()

