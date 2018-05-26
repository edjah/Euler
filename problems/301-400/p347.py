from time import perf_counter
from lib.prime import prime_sieve
from math import log
start = perf_counter()

primes = prime_sieve(10 ** 7 // 2)

def M(p, q, N):
    if p * q > N:
        return 0
    r = p
    answers = []
    while r <= N // q:
        s = r * q
        while s <= N:
            s *= q
        answers.append(s // q)
        r *= p
    return max(answers)

def S(N):
    tot = 0
    n = len(primes)
    for p in range(n):
        for q in range(p + 1, n):
            if primes[p] * primes[q] > N:
                break
            tot += M(primes[p], primes[q], N)
    return tot

ans = S(10 ** 7)
print('Solution:', ans)


end = perf_counter()
print(end - start, 'seconds to run')
