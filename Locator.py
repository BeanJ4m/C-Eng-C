import geopy.distance
import Classes

def distanceFinder(node1, node2):
    return geopy.distance.geodesic(node1.coords, node2.coords).km

def nodeLinker(node1, node2):
    dist = distanceFinder(node1, node2)
    time = dist/40

    way12.time = time
    way12.destination = node2

    way21.time = time
    way21.destination = node1

    node1.ways.append(way12)
    node2.ways.append(way21)
