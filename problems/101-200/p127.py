from time import perf_counter
from lib.prime import prime_factors_table
from itertools import permutations
from lib.partitions import partition
start = perf_counter()


def prod(a):
    x = 1
    for i in a:
        x *= i
    return x


lim = 120000
facs = [set(x) for x in prime_factors_table(lim)]

potential_rads = [(6, {2, 3})]
for i, s in enumerate(facs):
    if 2 < i < lim - 1 and i == prod(s) and len(s) >= 3:
        potential_rads.append((i, s))


def combos(nums, lim):
    nums = list(nums)
    n = len(nums)
    result = []

    def rec(x, idx):
        if x >= lim:
            return
        if idx >= n:
            result.append(x)
            return
        rec(x * nums[idx], idx)
        rec(x * nums[idx], idx + 1)

    rec(1, 0)
    return sorted(result)


def test(nums, rad):
    work = []
    P3 = list(partition(nums, 3))
    P2 = [x + [[]] for x in partition(nums, 2)]
    for p in P2 + P3:
        for A, B, C in permutations(p):
            A = combos(A, lim)
            B = combos(B, lim)
            C = set(C)

            for b in B:
                for a in A:
                    c = a + b
                    if a >= b or c >= lim:
                        break
                    if rad < c and facs[c] == C:
                        work.append((a, b, c))

    return work


work = []
for rad, nums in potential_rads:
    work.extend(test(nums, rad))

work = list(set(work))
print(len(work))


ans = sum(x[2] for x in work)
print('Solution:', ans)


end = perf_counter()
print(end - start, 'seconds to run')
