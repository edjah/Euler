from time import perf_counter
from datastructures import PriorityQueue, Graph
start = perf_counter()

def prim_mst(G):
    pq = PriorityQueue()
    pq.insert(0, 0)
    seen = [False] * G.size()
    dist = [float('inf')] * G.size()
    dist[0] = 0
    while pq.size() != 0:
        v = pq.pop()[1]
        seen[v] = True
        for e in G.adj[v]:
            w = e.other(v)
            if not seen[w] and dist[w] > e.weight:
                dist[w] = e.weight
                pq.insert(w, dist[w])
    return sum(dist)

mat = [[None] * 40 for i in range(40)]
with open('p107_network.txt', 'r') as f:
    for i, line in enumerate(f):
        for j, c in enumerate(line.rstrip().split(',')):
            if c == '-': continue
            mat[i][j] = int(c)

edges = []
for i in range(len(mat) - 1):
    for j in range(i + 1, len(mat)):
        if mat[i][j] != None:
            edges.append((i, j, mat[i][j]))

graph = Graph(len(mat), edges)
redudant_weight = sum(e[2] for e in edges)
mst = prim_mst(graph)
print('Redudant:', redudant_weight)
print('MST Weight:', mst)
print('Solution:', redudant_weight - mst)


end = perf_counter()
print(end - start, 'seconds to run')
