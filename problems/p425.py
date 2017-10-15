from time import perf_counter
from prime import read_primes
start = perf_counter()

primes = read_primes(10 ** 4)

p_digit_primes = {i:set() for i in range(1, 5)}
for p in primes:
    p_digit_primes[len(str(p))].add(p)

for p in p_digit_primes:
    print(p, p_digit_primes[p])

def chain(p):
    s = str(p)





end = perf_counter()
print(end - start, 'seconds to run')
