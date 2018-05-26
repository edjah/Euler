from time import perf_counter
import lib.prime as prime
from lib.prime import miller_rabin

def hamming_nums(n):
    nums = []
    primes = [2, 3, 5]
    def helper(idx, k):
        if k > n:
            return
        nums.append(k)
        for i in range(idx, 3):
            helper(i, k * primes[i])
    helper(0, 1)
    return nums



primes = set(prime.init(10 ** 8))
lim = 10 ** 8
def is_prime(n):
    if n <= lim:
        return n in primes
    else:
        return miller_rabin(n)

start = perf_counter()
N = 10 ** 8
H = hamming_nums(N)
print('len(H):', len(H))

ans = set()
iterations = 0
def rec(idx, k):
    global iterations
    if k in ans:
        iterations += 1
        return
    iterations += 1
    ans.add(k)
    for i in range(idx, len(H)):
        if k * H[i] <= N:
            rec(i + 1, k * H[i])
            a = H[i] + 1
            if k * a <= N and is_prime(a):
                rec(i + 1, k * a)

k = 396762170

rec(1, 1)
print('iterations:', iterations)
print('Len ans:', len(ans), len(H) ** 2)
print('Solution:', sum(ans))


end = perf_counter()
print(end - start, 'seconds to run')
