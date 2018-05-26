from time import perf_counter
from lib.prime import prime_sieve, miller_rabin
start = perf_counter()

primes = prime_sieve(30)

def admissible_nums(n):
    nums = []
    def helper(k, idx):
        if k > n or idx >= len(primes):
            return
        nums.append(k)
        helper(k * primes[idx], idx)
        helper(k * primes[idx + 1], idx + 1)
    helper(2, 0)
    return nums

def pseudo_fortunate(n):
    t = n + 2
    while not miller_rabin(t):
        t += 1
    return t - n

pseudos = set()
admissibles = admissible_nums(10 ** 9)

for x in admissibles:
    pseudos.add(pseudo_fortunate(x))

solution = sum(pseudos)
print('Solution:', solution)
print('Admissibles length:', len(admissibles))
print('pseudo-Forunates length:', len(pseudos))


end = perf_counter()
print(end - start, 'seconds to run')
