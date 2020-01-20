from lib.utility import start_time, end_time
from lib.datastructures import Graph
from collections import defaultdict
from itertools import permutations
from math import acos, pi
start_time()

square_sums = defaultdict(list)

limit = 2 ** 15
for m in range(2 ** 8):
    for n in range(2 ** 8):
        if m**2 + n**2 > limit:
            break
        square_sums[m**2 + n**2].append((m, n))


def quadruples(d):
    results = [
        (-d, 0, 0, d), (d, 0, 0, d),
        (0, -d, 0, d), (0, d, 0, d),
        (0, 0, -d, d), (0, 0, d, d),
    ]
    for m_plus_n in sorted(square_sums.keys()):
        if m_plus_n > d:
            break

        for (p, q) in square_sums[d - m_plus_n]:
            for (m, n) in square_sums[m_plus_n]:
                a = m*m + n*n - p*p - q*q
                b = 2 * (m*q + n*p)
                c = 2 * (n*q - m*p)
                assert d == m*m + n*n + p*p + q*q
                assert a*a + b*b + c*c == d*d
                results.append(tuple(sorted((a, b, c, d))))

    permuted_results = []
    for (a, b, c, _) in results:
        for (x, y, z) in permutations((a, b, c)):
            permuted_results.append((x, y, z, d))
            permuted_results.append((x, -y, z, d))
            permuted_results.append((x, y, -z, d))
            permuted_results.append((x, -y, -z, d))

            permuted_results.append((-x, y, z, d))
            permuted_results.append((-x, -y, z, d))
            permuted_results.append((-x, y, -z, d))
            permuted_results.append((-x, -y, -z, d))

    results = set(permuted_results)
    results.discard((0, d, 0, d))
    results.discard((0, -d, 0, d))
    return [(0, -d, 0, d)] + sorted(results) + [(0, d, 0, d)]


def distance(a, b):
    assert a[3] == b[3]
    dot_product = (a[0]*b[0] + a[1]*b[1] + a[2]*b[2]) / (a[3] ** 2)
    return (acos(dot_product) / pi) ** 2


def shortest_distance(r):
    print(r)
    start_time()
    quads = quadruples(r)
    print('Generating quadruples took: ', end='')
    end_time()

    start_time()
    graph = Graph(len(quads))
    print(len(quads))
    for i in range(len(quads)):
        for j in range(i + 1, len(quads)):
            graph.add_edge(i, j, distance(quads[i], quads[j]))
    print('Making graph took: ', end='')
    end_time()

    start_time()
    result = graph.dijkstra(0)['dist'][-1]
    print('Dijkstra took:', end='')
    end_time()
    print()
    return result


print(shortest_distance(7))

dist = 0
for n in range(1, 16):
    dist += shortest_distance(2 ** n - 1)

print(f'{dist:.10f}')

end_time()
