from time import perf_counter
start = perf_counter()

triples = set()
def add_triples(m, n, lim):
    t = 2*m*m + 2*m*n
    o = tuple(sorted((m*m - n*n, 2*m*n, m*m + n*n)))
    if o not in triples:
        for k in range(1, lim // t + 1):
            triples.add((k * o[0], k * o[1], k * o[2]))

for m in range(1, 1000):
    for n in range(1, m):
        add_triples(m, n, 4 * 10 ** 6)

print(len(triples))

d = {}
for a, b, c in triples:
    if a in d:
        d[a].add(b)
    else:
        d[a] = {b}
    if b in d:
        d[b].add(a)
    else:
        d[b] = {a}


def min_dist(a, b, c):
    d = (a + b) ** 2 + c ** 2
    d = min(d, (a + c) ** 2 + b ** 2)
    d = min(d, a ** 2 + (b + c) ** 2)
    return d ** 0.5

cache = {}
def count(m):
    if m <= 2:
        return 0
    elif m in cache:
        return cache[m]
    tot = count(m - 1)

    for x in d[m]:
        for i in reversed(range(1, min(m, x) + 1)):
            if x - i >= m or x - i > i:
                break
            if (x - i == 0):
                continue
            a = min_dist(i, x - i, m)
            if a == int(a):
                tot += 1
    cache[m] = tot
    return tot

m = 1
while count(m) <= 10 ** 6:
    print(m, ':', count(m))
    m += 1

print('Solution:', m)


end = perf_counter()
print(end - start, 'seconds to run')
