class Node:
    def __init__(self):
        self.package = bool
        self.num_package = int
        self.nodeID = int
        self.coords = (float, float)
        self.ways = [Way]


class Bots:
    def __int__(self):
        self.nameID = int
        self.location = int
        self.capacity = int
        self.storage = []
        self.journey = int


class Way:
    def __init__(self):
        self.time = float
        self.destination = Node


class Package(Node, Bots):
    def __int__(self):
        self.destination = int
        self.delivered = bool
        self.source = int
