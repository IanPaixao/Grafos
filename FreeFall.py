import networkx as nx
import math

class coordinates:
    def __init__(self,x,y):
        self.x = float(x)
        self.y = float(y)

def distance(coord1, coord2):
    return math.sqrt((coord1.x - coord2.x)**2 + (coord1.y - coord2.y)**2)


cases = int(input()) #number of cases

for x in range(cases):
    g = nx.Graph()
    coordinates_list = []
    totalw = 0
    numbercoordinates = int(input()) # number of coordinates
    for i in range(numbercoordinates):
        numbers = list(map(float, input().split()))
        coordinates_list.append(coordinates(numbers[0],numbers[1])) #read coordinates
        g.add_node(i)
        if len(coordinates_list) > 1:
            for j in range(i):
                g.add_edge(j,i, weight=distance(coordinates_list[j],coordinates_list[i])) # generate a complete graph

    tree = nx.minimum_spanning_tree(g, algorithm='kruskal') # mst

    for (n,a,w) in tree.edges.data('weight'):
        totalw += w #sum

    print('{0:.2f}'.format(totalw/100))
