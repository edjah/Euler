from time import perf_counter
start = perf_counter()

cache = {}
def ways(n, m):
    if (n, m) in cache:
        return cache[(n, m)]
    if n < 0:
        return 0
    elif n == 0:
        return 1
    t = 0
    for i in range(m, n + 1):
        t += ways(n - i, i)
    cache[(n, m)] = t
    return t

solution = ways(100, 1) - 1
print('Solution:', solution)


end = perf_counter()
print(end - start, 'seconds to run')
