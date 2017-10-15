from time import perf_counter
from prime import read_primes
start = perf_counter()

primes = read_primes(1000)
cache = {}
def ways(n, m):
    if (n, m) in cache:
        return cache[(n, m)]
    if n < 0:
        return 0
    elif n == 0:
        return 1
    t = 0
    for i in range(m, len(primes)):
        if primes[i] > n:
            break
        t += ways(n - primes[i], i)
    cache[(n, m)] = t
    return t

i = 0
while ways(i, 0) < 5000:
    i += 1
print('Solution:', i)
print('Num ways:', ways(i, 0))


end = perf_counter()
print(end - start, 'seconds to run')
