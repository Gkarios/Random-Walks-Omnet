import re

input_file = "nodes.txt"   # file with lines like: n0: Node @display("p=22607,17387");
output_file = "coords.ini"

pattern = re.compile(r"n(\d+): Node @display\(\"p=(\d+),(\d+)\"\);")

with open(input_file, "r", encoding="utf-8") as f_in, open(output_file, "w", encoding="utf-8") as f_out:
    for line in f_in:
        match = pattern.search(line)
        if match:
            idx, x, y = match.groups()
            f_out.write(f"**.node[{idx}].xCor = {x}\n")
            f_out.write(f"**.node[{idx}].yCor = {y}\n")

print(f"Converted coordinates written to {output_file}")

