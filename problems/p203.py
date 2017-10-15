from time import perf_counter
from prime import read_primes
from utility import nCr_tbl
start = perf_counter()

primes = read_primes(2 * 10 ** 7)

def squarefree(n):
    i = 0
    while primes[i] ** 2 <= n:
        if n % (primes[i] ** 2) == 0:
            return False
        i += 1
    return True

nums = sum((nCr_tbl(i) for i in range(51)), [])
ans = sum(set(filter(squarefree, nums)))

print('Solution:', ans)


end = perf_counter()
print(end - start, 'seconds to run')
