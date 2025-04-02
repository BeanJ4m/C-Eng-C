#code from https://www.geeksforgeeks.org/read-json-file-using-python/
# Python program to read
# json file

import Classes
import json

def JSONinit():
    # JSON file
    f = open('TA2.json', "r")
    json_string = f.read()

    # Reading from file
    data = json.loads(json_string)

    # Iterating through the json list
    packages = []
    bots = []
    id = 0
    for i in data['packages']:
        x = i.get('source')
        y = i.get('destination')
        newPackage = Classes.Package()
        newPackage.source = x
        newPackage.destination = y
        newPackage.delivered = False
        packages.append(newPackage)

    for j in data['bots']:
        x = j.get('location')
        y = j.get('capacity')
        newBot = Classes.Bots()
        newBot.location = x
        newBot.capacity = y
        newBot.nameID = id
        id += 1
        newBot.storage = []
        bots.append(newBot)


    return packages, bots
    # Closing file
    f.close()

P, B  = JSONinit()

for i in P:
    print(i.destination)
    print(i.source)

for j in B:
    print(j.nameID)
    print(j.location)
    print(j.capacity)