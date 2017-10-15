from time import perf_counter
from prime import prime_factors_table
start = perf_counter()

cache = {}
def partition(N):
    if N in cache:
        return cache[N]
    elif N <= 1:
        return {()}
    parts = set()
    for i in range(2, N + 1):
        if N % i == 0:
            for j in partition(N // i):
                parts.add(tuple(sorted((i,) + j)))
    cache[N] = parts
    return parts


N = 12000
optimals = [float('inf')] * (N + 2)

def try_prod(n):
    for part in partition(n):
        x = n - sum(part) + len(part)
        if x <= N and n < optimals[x]:
            optimals[x] = n


for i in range(int(N * 1.1)):
    if i % 200 == 0:
        print(i)
    try_prod(i)


sol = sum({optimals[k] for k in range(2, N + 1)})
print(sol)

end = perf_counter()
print(end - start, 'seconds to run')


