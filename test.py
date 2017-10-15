from primes import miller_rabin, sieve_array
from time import clock

primes = sieve_array(10 ** 5)
prime_factors_cache = {}
def prime_factors(n):
    orig = n
    if n in prime_factors_cache:
        return prime_factors_cache[n]

    if miller_rabin(n):
        prime_factors_cache[n] = [n]
        return [n]

    c = 0
    facs = []
    while n != 1:
        if n % primes[c] == 0:
            facs.append(primes[c])
            n //= primes[c]
            c = -1
        c += 1

    prime_factors_cache[orig] = facs
    return facs

def contains_all(big, little):
    m = len(big)
    c = 0
    for n in little:
        while c < m:
            if n == big[c]:
                c += 1
                break
            c += 1
        else:
            return False
    return True

factorial_fac_cache = {}
def factorial_prime_fac(n):
    if n in factorial_fac_cache:
        return factorial_fac_cache[n]

    factorial_factors = []
    for j in range(1, n + 1):
        factorial_factors.extend(prime_factors(j))
    factorial_factors.sort()
    factorial_fac_cache[n] = factorial_factors
    return factorial_factors

def s(n):
    facs = prime_factors(n)
    for i in range(2, n):
        if contains_all(factorial_prime_fac(i), facs):
            return i
    return n

def S(n):
    tot = 0
    for i in range(2, n + 1):
        k = s(i)
        # print(i, '-', k)
        tot += k
    return tot

start = clock()

print(S(10 ** 3))
end = clock()

print(end - start, "seconds to run")
print((end - start) * 10**5, "seconds for all")
