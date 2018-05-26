from time import perf_counter
from lib.prime import prime_factors_table
start = perf_counter()

factors = prime_factors_table(10 ** 5)
def rad(n):
    prod = 1
    for x in set(factors[n]):
        prod *= x
    return prod

a = [(i, rad(i)) for i in range(1, 10 ** 5 + 1)]
E = [(0, 0)] + sorted(a, key=lambda x : x[1])
print('Solution:', E[10000])


end = perf_counter()
print(end - start, 'seconds to run')
