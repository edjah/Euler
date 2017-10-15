from time import perf_counter
from prime import read_primes
start = perf_counter()

N = 10 ** 8
primes = read_primes(N)
mod = 1000000009

t = 1
for p in primes:
    e = c = N // p
    while c > 0:
        c //= p
        e += c
    t = t * (pow(p, 2 * e, mod) + 1) % mod

print('Solution:', t)


end = perf_counter()
print(end - start, 'seconds to run')
