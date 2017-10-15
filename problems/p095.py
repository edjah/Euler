from time import perf_counter
start = perf_counter()

def divisor_sum_tbl(n):
    tbl = [0] * (n + 1)
    for i in range(1, n + 1):
        for j in range(i + i, n + 1, i):
            tbl[j] += i
    return tbl

limit = 10 ** 6
divisor_sums = divisor_sum_tbl(limit)

cache = {}
def chain(start, lim):
    if start in cache:
        return cache[start]
    s = divisor_sums[start]
    c = {start}
    while s != start:
        if s > lim or s == 0 or s in c:
            return []
        c.add(s)
        s = divisor_sums[s]

    for x in c:
        cache[x] = c

    return c


ans = (0, [])
for i in range(limit + 1):
    k = chain(i, limit)
    if len(k) > ans[0]:
        ans = (len(k), k)

print('Length:', ans[0])
print('Solution:', min(ans[1]))


end = perf_counter()
print(end - start, 'seconds to run')
