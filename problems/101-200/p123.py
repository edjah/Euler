from lib.utility import start_time, end_time
from lib.prime import read_primes
start_time()

primes = read_primes(10 ** 6)


def r(n):
    p = primes[n - 1]
    p_sq = p * p
    x = pow(p - 1, n, p_sq) + pow(p + 1, n, p_sq)
    return x % p_sq


n = 1
goal = 10 ** 10
while r(n) <= goal:
    n += 1

print('Solution:', n)
end_time()
