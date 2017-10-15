from time import perf_counter
from prime import read_primes
from fractions import Fraction
start = perf_counter()

limit = 10 ** 2
primes = read_primes(limit)
prime_set = set(primes)

n = len(primes)

def prod(a):
    p = 1
    for i in a:
        p *= i
    return p

r = []
for i in range(n - 1):
    x = Fraction(primes[i + 1] + 1, primes[i] + 1)
    r.append(x)

for i in range(n - 1):
    a = [(primes[j],str(prod(r[i:j]))) for j in range(i + 1, n - 1)]
    print(primes[i],':', *a)
    print()




end = perf_counter()
print(end - start, 'seconds to run')
