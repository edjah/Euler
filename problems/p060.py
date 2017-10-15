from time import perf_counter
from prime import read_primes, miller_rabin
start = perf_counter()

primes = read_primes(10 ** 4)


def prime_pairs():
    n = len(primes)
    pairs = []
    for i in range(1, n - 1):
        for j in range(i + 1, n):
            a, b = str(primes[i]), str(primes[j])
            if miller_rabin(int(a + b)) and miller_rabin(int(b + a)):
                pairs.append((primes[i], primes[j]))
    return pairs

def prime_sets(old_sets, check_set):
    sets = []
    n = len(old_sets)
    for s in old_sets:
        for p in primes:
            if all(p > x for x in s):
                if all((x, p) in check_set for x in s):
                    sets.append((*s, p))

    if len(sets) == 0:
        print('Unable to find a solution!')
        return [(float('inf'),)]
    return sets

primes = primes[:1060]
a = set(prime_pairs())
print('Len2:', len(a))
print('Ans2:', min(a, key=lambda x:sum(x)))

b = set(prime_sets(a, a))
print('\nLen3:', len(b))
print('Ans3:', min(b, key=lambda x:sum(x)))

c = set(prime_sets(b, a))
print('\nLen4:', len(c))
print('Ans4:', min(c, key=lambda x:sum(x)))

d = set(prime_sets(c, a))
print('\nLen5:', len(d))
print('Ans5:', min(d, key=lambda x:sum(x)))

print('\nSolution:', sum(min(d, key=lambda x:sum(x))))


end = perf_counter()
print()
print(end - start, 'seconds to run')
