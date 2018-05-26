from time import perf_counter
from lib.prime import read_primes
from lib.utility import nCr_tbl
start = perf_counter()

def g_hamming_nums(lim, n):
    primes = read_primes(n)
    nums = []
    seen = set()
    def helper(k):
        if k > lim or k in seen:
            return
        nums.append(k)
        seen.add(k)
        for i in primes:
            helper(k * i)
    helper(1)
    return nums

ans = g_hamming_nums(10 ** 9, 100)
print('Solution:', len(ans))



end = perf_counter()
print(end - start, 'seconds to run')
