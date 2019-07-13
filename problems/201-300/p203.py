from lib.utility import start_time, end_time, nCr_tbl
from lib.prime import read_primes
start_time()


limit = 51
primes = read_primes(2 * limit)


def squarefree_nCr(n):
    i = 0
    while primes[i] < limit:
        if n % (primes[i] ** 2) == 0:
            return False
        i += 1
    return True


nums = sum((nCr_tbl(i) for i in range(limit)), [])
ans = sum(set(filter(squarefree_nCr, nums)))

print('Solution:', ans)
end_time()
