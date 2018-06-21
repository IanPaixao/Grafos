import networkx as nx
import math

class coordenadas:
    def __init__(self,x,y):
        self.x = float(x)
        self.y = float(y)

def distancia(coord1, coord2):
    return math.sqrt((coord1.x - coord2.x)**2 + (coord1.y - coord2.y)**2)

# execucao principal
casos_teste = int(input()) #le os casos de teste

for x in range(casos_teste):
    grafo = nx.Graph()
    historico = []
    peso_total = 0
    pontos = int(input()) #le a quantidade de coordenadas a serem processadas
    for i in range(pontos):
        numbers = list(map(float, input().split()))
        historico.append(coordenadas(numbers[0],numbers[1])) #le as coordenadas e as guarda em um historico
        grafo.add_node(i)
        if len(historico) > 1:
            for j in range(i):
                grafo.add_edge(j,i, weight=distancia(historico[j],historico[i])) #gera um grafo completo com peso nas arestas

    arvore = nx.minimum_spanning_tree(grafo, algorithm='kruskal') #arvore geradora minima, para que se tenha as arestas mais leves do grafo

    for (n,a,w) in arvore.edges.data('weight'):
        peso_total += w #soma o peso de todas as arestas

    print('{0:.2f}'.format(peso_total/100))
