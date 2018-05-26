from time import perf_counter
from lib.prime import prime_factors_table
from itertools import combinations
from functools import reduce
start = perf_counter()


facs = prime_factors_table(10 ** 6)


def prod(a):
    return reduce(lambda x, y: x * y, a)


def num_solutions(n):
    uniq = set(facs[n])
    nums = [2 * facs[n].count(x) for x in sorted(uniq)]

    count = 1
    if (n == 180180):
        print(nums)
    for m in range(1, len(nums) + 1):
        for tup in combinations(nums, m):
            count += prod(tup)

    return (count + 1) // 2


best = 0
for n in range(10 ** 6):
    x = num_solutions(n)
    if x > best:
        print(f"New best: {n} has {x} solutions")
        best = x

    if x > 1000:
        break

end = perf_counter()
print(f"{end - start:f} seconds to run")
