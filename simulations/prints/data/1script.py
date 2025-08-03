import glob
import numpy as np
import matplotlib.pyplot as plt

files = glob.glob("qtcmd/unique_visited_nodes_run*.txt")
data = []

num_nodes = 50 # Set this to your actual node count

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

# Plotting
plt.figure(figsize=(10, 7))
plt.plot(range(len(avg)), avg, label="RW Coverage", color="#1f77b4", linewidth=2)

# Annotate final point
final_x = len(avg) - 1
final_y = avg[-1]
plt.scatter([final_x], [final_y], color="red")
plt.annotate(f"End: ({final_x}, {final_y:.2f})", (final_x, final_y), textcoords="offset points", xytext=(-40,10), ha='right')

plt.xlabel("Hops")
plt.ylabel("Uniquely visited nodes")
plt.title("Random Walker Network Coverage (Averaged over 500 runs)")
plt.grid(True)
plt.ylim(0, num_nodes + 2)
#plt.ylim(49.9, 50)
plt.xlim(0, len(avg) + 2)
plt.legend()
plt.tight_layout()
plt.savefig("average_coverage.png")
plt.show()
