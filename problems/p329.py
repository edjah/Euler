from time import perf_counter
from prime import read_primes
from fractions import Fraction
start = perf_counter()
primes = set(read_primes(501))

sequence = 'PPPPNNPPPNPPNPN'
cache = {}
def path(num, den, c, idx):
    tup = (num, den, c, idx)
    if tup in cache:
        return cache[tup]

    if idx >= len(sequence):
        return Fraction(num, den)

    if c in primes:
        mult = 2 if sequence[idx] == 'P' else 1
    else:
        mult = 1 if sequence[idx] == 'P' else 2

    t = 0
    if 1 < c < 500:
        t += path(num * mult, den * 6, c - 1, idx + 1)
        t += path(num * mult, den * 6, c + 1, idx + 1)
    elif c == 1:
        t += path(num * mult, den * 3, c + 1, idx + 1)
    elif c == 500:
        t += path(num * mult, den * 3, c - 1, idx + 1)

    cache[tup] = t
    return t

t = 0
for s in range(1, 501):
    t += path(1, 1, s, 0) / 500
print('Solution:', t)
print('Solution:', t * 1.0)

end = perf_counter()
print('\n%f seconds to run' % (end - start))
