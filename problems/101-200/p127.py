from lib.utility import start_time, end_time, product
from lib.prime import prime_factors_table
from lib.partitions import partition
from itertools import permutations
start_time()


limit = 120000
distinct_prime_factors = [set(x) for x in prime_factors_table(limit)]

potential_rads = [(6, {2, 3})]
for i, s in enumerate(distinct_prime_factors):
    if 2 < i < limit - 1 and i == product(s) and len(s) >= 3:
        potential_rads.append((i, s))


def combos(prime_factors):
    prime_factors = list(prime_factors)
    n = len(prime_factors)
    result = []

    def rec(x, idx):
        if x >= limit:
            return
        if idx >= n:
            result.append(x)
            return
        rec(x * prime_factors[idx], idx)
        rec(x * prime_factors[idx], idx + 1)

    rec(1, 0)
    return sorted(result)


def compute_abc_hits(rad, prime_factors):
    abc_hits = []
    P3 = list(partition(prime_factors, 3))
    P2 = [x + [[]] for x in partition(prime_factors, 2)]
    for p in P2 + P3:
        for A, B, C in permutations(p):
            A = combos(A)
            B = combos(B)
            C = set(C)

            for b in B:
                for a in A:
                    c = a + b
                    if a >= b or c >= limit:
                        break
                    if rad < c and distinct_prime_factors[c] == C:
                        abc_hits.append((a, b, c))

    return abc_hits


work = []
for rad, prime_factors in potential_rads:
    work += compute_abc_hits(rad, prime_factors)

ans = sum(x[2] for x in set(work))
print('Solution:', ans)
end_time()
