from coverage_utils import load_coverage_data
import matplotlib.pyplot as plt

num_nodes = 145
experiments = [
    ("taxi_normal_rw", "taxi - 1rw"),
    ("taxi-duplication", "taxi  - rw cloning (Clone Interval = 1000 hops)"),
    ("taxi-no-backtracking", "taxi - no backtracking"),
    ("taxi-hybrid-d-b", "taxi - cloning & no backtracking")
]
colors = ["#1f77b4", "#2ca02c", "#d62728", "#b495c2"]

plt.figure(figsize=(10, 6))
ax = plt.gca()
ax.set_facecolor("#f9f9f9")


for (folder, label), color in zip(experiments, colors):
    x, y = load_coverage_data(folder, num_nodes, label, threshold=100)
    plt.plot(x, y, label=label, linewidth=2.5, color=color)

    # Annotate final point
    final_x, final_y = x[-1], y[-1]
    plt.scatter([final_x], [final_y], color=color, zorder=5)
    plt.annotate(
        f"End: {final_x}",
        xy=(final_x, final_y),
        xytext=(-60, 15),
        textcoords="offset points",
        fontsize=9,
        arrowprops=dict(arrowstyle="->", color=color),
        bbox=dict(boxstyle="round,pad=0.3", fc="white", ec=color, lw=0.8)
    )

    # Add vertical milestone lines for 50% and 90%
    for milestone in [50, 90]:
        idx = next((i for i, val in enumerate(y) if val >= milestone), None)
        if idx is not None:
            plt.axvline(x=idx, color=color, linestyle='--', alpha=0.3)
            plt.text(idx + 1, 5, f"{idx}", rotation=90, fontsize=8, color=color)

# Global horizontal milestone lines
for y_val in [50, 90]:
    plt.axhline(y=y_val, color='gray', linestyle='--', linewidth=1, alpha=0.5)
    plt.text(0, y_val + 1, f"{y_val}%", color='gray', fontsize=9)

plt.title("Random Walker Network 100% Coverage - Comparing four algorithms", fontsize=14, weight='bold')
plt.xlabel("Hops (t)", fontsize=12)
plt.ylabel("Coverage (%)", fontsize=12)
plt.ylim(0, 105)
plt.grid(True, linestyle='--', alpha=0.5)
plt.legend(title="Walker Count", fontsize=10, title_fontsize=11)
plt.tight_layout()
plt.savefig("walker_comparison.png", dpi=300)
plt.show()

