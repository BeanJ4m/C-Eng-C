from xml.dom import minidom
import xml.etree.ElementTree as ET
import Classes

file = minidom.parse('TA2.XML')


def XMLinit(xml_file_path):
    tree = ET.parse(xml_file_path)
    root = tree.getroot()
    nodes = []
    newNode = Classes.Node()
    id = 0
    for node in root.findall(".//node"):
        lat_elem = node.find("lat")
        lon_elem = node.find("lon")
        lat_values = []
        lon_values = []
        if lat_elem is not None:
            lat_values.append(float(lat_elem.text))
        if lon_elem is not None:
            lon_values.append(float(lat_elem.text))

        newNode.coords = (lat, lon)
        newNode.nodeID = id
        id += 1
        newNode.package = False
        newNode.num_package = 0
        newNode.ways = []
        nodes.append(newNode)

    return nodes


k = XMLinit('TA2.XML')

print(k)
for i in k:
    print(i.nodeID)
    print(i.coords)