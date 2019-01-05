from lib.datastructures import PriorityQueue


class Node:
    def __init__(self, val):
        self.val = val
        self.adj = []


def dijkstra(graph, s):
    n = len(graph)
    pq = PriorityQueue()
    pq.insert(s, 0)
    visited = [False] * n
    dist = [float('inf')] * n

    while pq.size() != 0:
        w, v = pq.pop()
        dist[v] = w
        visited[v] = True
        for x in graph[v].adj:
            if not visited[x]:
                dist[x] = min(dist[x], w + graph[x].val)
                pq.insert(x, dist[x])

    return {'dist': dist}
