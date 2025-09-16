import glob
import numpy as np
import matplotlib.pyplot as plt

# Load and preprocess data
files = glob.glob("qtcmd/unique_visited_nodes_run*.txt")
data = []

num_nodes = 50  # Set this to your actual node count
coverage_threshold = 0.9995  # 99.95%

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

# Find the first timestep where coverage reaches the threshold
stop_idx = next((i for i, v in enumerate(percent_coverage) if v >= coverage_threshold * 100), len(percent_coverage) - 1)

# Truncate data at that point
timesteps = range(stop_idx + 1)
percent_coverage = percent_coverage[:stop_idx + 1]
import matplotlib.pyplot as plt

# ... [your data processing code] ...

plt.figure(figsize=(10, 6))

# Light background color
ax = plt.gca()
ax.set_facecolor("#f9f9f9")  # soft gray

# Main line
plt.plot(timesteps, percent_coverage, label="RW Coverage (%)", color="#007acc", linewidth=2.5)

# Annotate the final point
final_x = timesteps[-1]
final_y = percent_coverage[-1]
plt.scatter([final_x], [final_y], color="red", zorder=5)
plt.annotate(
    f"End: {final_x} time slots\n{final_y:.2f}%",
    xy=(final_x, final_y),
    xytext=(-80, 10),
    textcoords="offset points",
    fontsize=10,
    arrowprops=dict(arrowstyle="->", color="black"),
    bbox=dict(boxstyle="round,pad=0.3", fc="white", ec="black", lw=0.5)
)
# Add milestone lines with both horizontal and vertical lines
milestones = [50, 90]
for y in milestones:
    # Horizontal line at y%
    plt.axhline(y=y, color='gray', linestyle='--', linewidth=1, alpha=0.5)
    plt.text(timesteps[0], y + 1.5, f'{y}%', color='gray', fontsize=9)

    # Find the x (hop) where we first reach that % coverage
    x_milestone = next((i for i, val in enumerate(percent_coverage) if val >= y), None)
    if x_milestone is not None:
        # Vertical line at that hop
        plt.axvline(x=x_milestone, color='gray', linestyle='--', linewidth=1, alpha=0.5)
        plt.text(x_milestone + 1, 5, f'{x_milestone} time slots', rotation=90, fontsize=8, color='gray')

# Style
plt.title("Random Walker Network Coverage\n(Averaged over 500 runs)", fontsize=14, weight='bold')
plt.xlabel("Time Slots", fontsize=12)
plt.ylabel("Coverage (%)", fontsize=12)
plt.ylim(0, 105)
plt.xlim(0, final_x + 10)
plt.xticks(fontsize=10)
plt.yticks([0, 25, 50, 75, 90, 100], fontsize=10)
plt.grid(True, linestyle='--', alpha=0.4)
plt.legend(loc="lower right", fontsize=10, frameon=True)
plt.tight_layout()

# Save and show
plt.savefig("average_coverage_percent.png", dpi=300)
plt.show()

