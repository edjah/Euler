from prime import *
from time import perf_counter

start = perf_counter()
def concat_is_prime(a, b):
    a = str(a)
    b = str(b)

    return miller_rabin(int(a + b)) and miller_rabin(int(b + a))

primes = read_primes(10000)

prime_singles = [[x] for x in primes]
prime_pairs = []

for i in range(len(primes) - 1):
    for j in range(i + 1, len(primes)):
        if concat_is_prime(primes[i], primes[j]):
            prime_pairs.append((primes[i], primes[j]))

prime_pairs = set(prime_pairs)
def prime_groups(n):
    if n == 1:
        return prime_singles

    if n == 2:
        return prime_pairs

    groups = prime_groups(n - 1)

    if n == 3:
        groups = [list(group) for group in groups]

    l = []
    for group in groups:
        for prime in primes:
            if any(prime <= x for x in group):
                continue

            good = True
            for n in group:
                if (n, prime) not in prime_pairs:
                    good = False
                    break
            if good:
                temp = group[:]
                temp.append(prime)
                l.append(temp)

    return l

gs = prime_groups(5)

ans = min(sum(g) for g in gs)

print(ans)
end = perf_counter()
print('{:.4f} sec'.format(end - start))
