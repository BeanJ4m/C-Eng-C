import Classes
import Locator

packages = []
TIME = 0.0
undelivered = len(packages)

while undelivered > 0:

    for package in packages:
        if not package.delivered:
          pass
        elif package.delivered:
            undelivered -= 1


#def findPath(bot1, node1):


