from time import perf_counter
import lib.prime as prime
from heapq import *
start = perf_counter()

primes = prime.read_primes(10 ** 7)
heap = [2]

prod = 1
idx = 1
for i in range(500500):
    k = heappop(heap)
    prod = (prod * k) % 500500507
    heappush(heap, k * k)
    heappush(heap, primes[idx])
    idx += 1

print('Solution:', prod)
end = perf_counter()
print(end - start, 'seconds to run')
