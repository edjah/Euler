from lib.utility import start_time, end_time
from lib.prime import read_primes
start_time()

primes = read_primes(5 * 10 ** 7)

tot = 0
limit = 10 ** 8
for i in range(len(primes)):
    for j in range(i, len(primes)):
        if primes[i] * primes[j] >= limit:
            break
        tot += 1

print('Solution:', tot)
end_time()
