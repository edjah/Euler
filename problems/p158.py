from time import perf_counter
start = perf_counter()

def p(n):
    if n == 3:
        return 26 * 25 * 16

import prime
prime.init(10 ** 5)

print(prime.prime_factors(10400))

print(p(3))


end = perf_counter()
print(end - start, 'seconds to run')
