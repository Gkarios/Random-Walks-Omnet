import xml.etree.ElementTree as ET

def dms_to_dd(degrees, minutes, seconds, direction):
    """
    Converts degrees, minutes, and seconds to decimal degrees.
    """
    dd = degrees + minutes / 60 + seconds / 3600
    if direction in ['S', 'W']:
        dd *= -1
    return dd

def normalize_and_scale_coordinates(lon, lat, min_lon, max_lon, min_lat, max_lat, canvas_width, canvas_height):
    """
    Normalizes coordinates to a 0-1 range and then scales them to a specific
    canvas size. The normalized_y value is inverted to account for Omnet++'s
    coordinate system, where y=0 is at the top of the canvas.
    """
    # Normalize coordinates to a 0-1 range
    normalized_x = (lon - min_lon) / (max_lon - min_lon)
    normalized_y = (max_lat - lat) / (max_lat - min_lat)
    
    # Scale the normalized coordinates to the canvas size
    scaled_x = normalized_x * canvas_width
    scaled_y = normalized_y * canvas_height
    
    return scaled_x, scaled_y

# Define the bounding box from the user's input
# Note: The original input was in DMS, which needs to be converted to decimal degrees.
# NE: 38°08'34"N 24°01'46"E
# SE: 37°48'08"N 24°01'46"E
# SW: 37°48'08"N 23°29'51" E
# NW: 38°08'34"N 23°29'51" E

# Manually converted to decimal degrees for the bounding box
min_lat = dms_to_dd(37, 48, 8, 'N')
max_lat = dms_to_dd(38, 8, 34, 'N')
min_lon = dms_to_dd(23, 29, 51, 'E')
max_lon = dms_to_dd(24, 1, 46, 'E')

# Define the size of the Omnet++ simulation canvas
canvas_width = 6000
canvas_height = 6000

# Read the KML file
kml_file = 'taxi_231002-1.kml'
tree = ET.parse(kml_file)
root = tree.getroot()

# The KML namespace needs to be handled to find the elements correctly
ns = {'kml': 'http://www.opengis.net/kml/2.2'}

# Find all Placemark elements
placemarks = root.findall('.//kml:Placemark', ns)

print(f"Coordinates formatted for omnet.ini with a {canvas_width}x{canvas_height} canvas:")
print("----------------------------------------------------------------------")

# Iterate through each placemark with an index to format the output correctly
for i, placemark in enumerate(placemarks):
    # Find the <Point> and then <coordinates> element
    coordinates_tag = placemark.find('.//kml:Point/kml:coordinates', ns)
    if coordinates_tag is not None:
        # The coordinates are a single string "longitude,latitude,altitude"
        lon_str, lat_str, _ = coordinates_tag.text.strip().split(',')
        
        # Convert to float
        lon = float(lon_str)
        lat = float(lat_str)
        
        # Normalize and scale the coordinates
        scaled_x, scaled_y = normalize_and_scale_coordinates(lon, lat, min_lon, max_lon, min_lat, max_lat, canvas_width, canvas_height)
        
        # Print the output in the desired format
        print(f"**.node[{i}].xCor = {int(scaled_x)}")
        print(f"**.node[{i}].yCor = {int(scaled_y)}")
        

