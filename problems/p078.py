from time import perf_counter
import sys
start = perf_counter()

cache = {}
def ways(n, m):
    if (n, m) in cache:
        return cache[(n, m)]
    if n < 0:
        return 0
    elif n == 0:
        return 1
    t = sum(ways(n - k, k) for k in range(m, n + 1))
    cache[(n, m)] = t
    return t

# D(i, j) = sum(D(i - k, k) for k in range(j, i + 1))
print(ways(400, 1))


end = perf_counter()
print(end - start, 'seconds to run')
