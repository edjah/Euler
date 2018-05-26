from time import perf_counter
from lib.prime import read_primes
start = perf_counter()

primes = read_primes(5 * 10 ** 7)

tot = 0
limit = 10 ** 8
for i in range(len(primes)):
    for j in range(i, len(primes)):
        if primes[i] * primes[j] >= limit:
            break
        tot += 1

print(tot)

end = perf_counter()
print(end - start, 'seconds to run')
