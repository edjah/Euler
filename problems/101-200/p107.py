from lib.utility import start_time, end_time
from lib.datastructures import Graph, UnionFind
start_time()


# kruskal's algorithm
def compute_mst_weight(G):
    total_dist = 0
    disjoint_set = UnionFind(G.size())
    for edge in sorted(G.edges, key=lambda e: e.weight):
        if disjoint_set.find(edge.a) != disjoint_set.find(edge.b):
            total_dist += edge.weight
            disjoint_set.union(edge.a, edge.b)

    return total_dist


def parse_edges():
    edges = []
    with open('files/p107_network.txt', 'r') as f:
        for i, line in enumerate(f):
            for j, c in enumerate(line.rstrip().split(',')):
                if c != '-' and i < j:
                    edges.append((i, j, int(c)))
    return edges


edges = parse_edges()
num_nodes = 1 + max(e[1] for e in edges)
graph = Graph(num_nodes, edges)
redundant = sum(e[2] for e in edges)
mst_weight = compute_mst_weight(graph)

print('Redundant:', redundant)
print('MST Weight:', mst_weight)
print('Solution:', redundant - mst_weight)
end_time()
