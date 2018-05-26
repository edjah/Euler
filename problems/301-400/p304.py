from lib.prime import miller_rabin
from time import perf_counter

start = perf_counter()
mod = 1234567891011

def nxt_prime(n):
    n += 1 if n % 2 == 0 else 2
    while not miller_rabin(n, 3):
        n += 2
    return n

cache = {}
def a(n):
    if n in cache:
        return cache[n]
    elif n <= 0:
        return None
    elif n == 1:
        return nxt_prime(10 ** 14)
    else:
        ans = nxt_prime(a(n - 1))
        cache[n] = ans
        return ans

def mat_mult(a, b, mod):
    w = (a[0]*b[0] + a[1]*b[2]) % mod
    x = (a[0]*b[2] + a[1]*b[3]) % mod
    y = (a[2]*b[0] + a[3]*b[2]) % mod
    z = (a[2]*b[1] + a[3]*b[3]) % mod
    a[0], a[1], a[2], a[3] = w, x, y, z

def fast_fibonacci(n):
    current = [0, 1, 1, 1]
    result = [1, 0, 0, 1]
    while n != 0:
        if n & 1 == 1:
            mat_mult(result, current, mod)
        mat_mult(current, current, mod)
        n >>= 1
    return result[1] % mod


tot = 0
for n in range(1, 100001):
    tot += fast_fibonacci(a(n))

print('Solution:', tot % mod)

end = perf_counter()
print(end - start, 'seconds to run')
