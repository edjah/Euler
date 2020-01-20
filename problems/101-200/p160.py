from lib.utility import start_time, end_time
from math import factorial, floor, ceil
start_time()

mod = 10 ** 3


def count_trailing_factorial_zeros(n):
    c, t = 0, 5
    while t <= n:
        c += n // t
        t *= 5
    return c


def naive(n):
    fac = factorial(n)
    zeros = count_trailing_factorial_zeros(n)
    return (fac // 10 ** zeros) % mod


def alternative1(n):
    counts = [0] * min(n + 1, mod)

    num_twos = count_trailing_factorial_zeros(n)
    for i in range(1, n + 1):
        while num_twos > 0 and i % 2 == 0:
            i //= 2
            num_twos -= 1

        while i % 5 == 0:
            i //= 5

        assert i % mod != 5
        counts[i % mod] += 1

    assert sum(counts) == n
    prod = 1
    for i in range(len(counts)):
        prod = (prod * pow(i, counts[i], mod)) % mod

    return prod


def alternative2(n):
    # we get n! % mod by first counting the number of times we use each factor
    # after counting, we can compute prod(i**count for i in range(mod)) % mod
    counts = [0] * mod

    # first counting the 0 < i < n s.t. i is not divisible by 2 or 5
    num_elements = n - floor(n / 2) - ceil(floor(n / 5) / 2)
    num_buckets = mod - floor(mod / 2) - ceil(floor(mod / 5) / 2)
    curr_bucket = 0

    for i in range(mod):
        if i % 2 == 0 or i % 5 == 0:
            continue

        # counts[i] += ceil(num_elements / num_buckets)
        # counts[i] -= curr_bucket >= (num_elements % num_buckets)
        # curr_bucket += 1

    # next, counting the 0 < i < n s.t. i = 0 mod 2
    num_twos = count_trailing_factorial_zeros(n)
    for i in range(1, n + 1):
        if not (i % 2 == 0 or i % 5 == 0):
            continue

        if num_twos > 0 and i % 2 == 0:
            i //= 2
            num_twos -= 1

        while i % 5 == 0:
            i //= 5

        assert i % mod != 5
        counts[i % mod] += 1

    # assert sum(counts) == n
    # cc = n - floor(n / 2) - ceil(floor(n / 5) / 2)
    # print(n, '|', n - sum(counts), cc)
    # assert n - sum(counts) == cc

    if n == 996:
        for j in range(mod):
            print(f'counts[{j}] = {counts[j]}')

    prod = 1
    for i in range(mod):
        prod = (prod * pow(i, counts[i], mod)) % mod

    return prod


for i in range(1, 1000):
    # print(i, '|', naive(i), 'vs', alternative(i))
    # assert (naive(i) == alternative2(i))
    alternative2(i)

goal = 10 ** 12
print(count_trailing_factorial_zeros(goal))

end_time()
