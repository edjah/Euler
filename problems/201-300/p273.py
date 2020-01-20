# the solution uses the following relation
# (a^2 + b^2)(c^2 + d^2) = (ac + bd)^2 + (ad - bc)^2 = (ad + bc)^2 + (ac - bd)^2

from lib.utility import start_time, end_time, memoize, subsets
from lib.prime import read_primes
start_time()


def decompose_prime_as_sum_of_squares(p):
    assert p % 4 == 1

    for i in range(1, int(p ** 0.5) + 1):
        j = round((p - i*i) ** 0.5)
        if j ** 2 == p - i*i:
            return (i, j)


@memoize
def ways_as_sum_of_squares(primes):
    pairs = []

    if len(primes) == 1:
        pairs.append(decompose_prime_as_sum_of_squares(primes[0]))

    elif len(primes) >= 2:
        a, b = decompose_prime_as_sum_of_squares(primes[0])
        for (c, d) in ways_as_sum_of_squares(primes[1:]):
            pairs.append((a*c + b*d, a*d - b*c))
            pairs.append((a*d + b*c, a*c - b*d))

    ways = []
    for pair in pairs:
        ways.append(tuple(sorted([abs(x) for x in pair])))
    return sorted(set(ways))


primes = [p for p in read_primes(150) if p % 4 == 1]

total = 0
for s in subsets(primes):
    total += sum(a for a, b in ways_as_sum_of_squares(s))

print('Solution:', total)
end_time()
