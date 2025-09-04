import xml.etree.ElementTree as ET
import pandas as pd

# Input / Output files
kml_file = "taxi_231002-1.kml"
ned_file = "TaxiNetwork.ned"

# Parse XML
tree = ET.parse(kml_file)
root = tree.getroot()

# Namespace for KML
ns = {"kml": "http://www.opengis.net/kml/2.2"}

# Collect Placemarks
rows = []
for pm in root.findall(".//kml:Placemark", ns):
    name = pm.find("kml:name", ns).text.strip()
    coords = pm.find(".//kml:coordinates", ns).text.strip()
    lon, lat, *_ = map(float, coords.split(","))
    rows.append({"name": name, "lat": lat, "lon": lon})

df = pd.DataFrame(rows)

# Normalize to OMNeT++ coordinate system
min_lat, min_lon = df["lat"].min(), df["lon"].min()

scale = 100000  # ~meters per degree in Athens area
df["x"] = (df["lon"] - min_lon) * scale
df["y"] = (df["lat"] - min_lat) * scale

# Write NED file
with open(ned_file, "w", encoding="utf-8") as f:
    f.write("network TaxiNetwork {\n")
    f.write("    submodules:\n")
    for i, row in df.iterrows():
        safe_name = f"n{i}"  # station names in Greek would break NED identifiers
        f.write(f'        {safe_name}: Node @display("p={row["x"]:.0f},{row["y"]:.0f}");\n')
    f.write("}\n")

print(f"✅ Exported {len(df)} nodes to {ned_file}")

