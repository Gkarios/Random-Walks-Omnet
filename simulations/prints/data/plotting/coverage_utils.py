def load_coverage_data(folder, num_nodes, label, threshold=99.5):
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

    # Truncate at first point where threshold is reached
    stop_idx = next((i for i, v in enumerate(percent_coverage) if v >= threshold), len(percent_coverage))
    percent_coverage = percent_coverage[:stop_idx + 1]
    timesteps = range(stop_idx + 1)

    return timesteps, percent_coverage

