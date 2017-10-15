from time import perf_counter
from graph import Node, dijkstra

start = perf_counter()
N = 80
with open("p083.txt", "r") as f:
    M = [[int(i) for i in x.split(',')] for x in f.readlines()]

graph = [Node(x) for x in sum(M, [])]
for x in range(N):
    for y in range(N):
        node = graph[N*y + x]
        if x != 0:
            node.adj.append(N*y + x-1)
        if x != N - 1:
            node.adj.append(N*y + x+1)
        if y != 0:
            node.adj.append(N*(y-1) + x)
        if y != N - 1:
            node.adj.append(N*(y+1) + x)

a = dijkstra(graph, 0)['dist']
print(a[-1] + graph[0].val)
end = perf_counter()
print('{:.5f} sec'.format(end - start))
