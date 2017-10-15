from time import perf_counter
from utility import nCr
import prime
start = perf_counter()

prime.init(10 ** 6)

n = 20000000
r = 15000000



a = nCr(14, 2)
print(a)
print(prime.prime_factors(a))


end = perf_counter()
print(end - start, 'seconds to run')
