import networkx as nx

g = nx.DiGraph()

while True:
  try:
    nomes = input().split()
  except EOFError:
    break
  finally:
    g.add_node(nomes[0])
    g.add_node(nomes[1])
    g.add_edge(nomes[0], nomes[1])
    
print(len(list(nx.simple_cycles(g))))


    
  



