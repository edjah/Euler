from time import perf_counter
from math import factorial
import prime
start = perf_counter()

primes = prime.init(10 ** 8)
prime_set = set(primes)

def condense(facs):
    a = set(facs)
    s = []
    for x in sorted(a):
        e = facs.count(x)
        s += ['%d^%d' % (x, e)]
    return ' * '.join(s)

def s(n):
    if n in prime_set:
        return n
    m = 1
    while factorial(m) % n != 0:
        m += 1
    return m

def S(n):
    return sum(s(i) for i in range(2, n + 1))

for i in range(2, 101):
    print(i, prime.prime_factors(i), s(i))


end = perf_counter()
print(end - start, 'seconds to run')
