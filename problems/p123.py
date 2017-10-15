from time import perf_counter
from prime import read_primes
start = perf_counter()

primes = read_primes(237740)
def k(n):
    p = primes[n - 1]
    p_sq = p * p
    x = pow(p - 1, n, p_sq) + pow(p + 1, n, p_sq)
    return x % p_sq

n = 1
goal = 10 ** 10
while k(n) <= goal:
    n += 1

print('Solution:', n)


end = perf_counter()
print(end - start, 'seconds to run')
