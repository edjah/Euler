from time import perf_counter
import prime
start = perf_counter()

lim = 10 ** 8
tbl = [None] * lim
primes = prime.read_primes(lim)[2:]

def extended_euclid(a, b):
    if b == 0:
        return (a, 1, 0)
    d1, s1, t1 = extended_euclid(b, a % b)
    d = d1
    s = t1
    t = s1 - (a // b) * t1
    return (d, s, t)

def mod_inv(a, m):
    if a == 0:
        return 0
    d, x, y = extended_euclid(a, m)
    if d != 1:
        raise Exception('gcd of %d and %d is not 1' % (a, m))
    return (x%m + m) % m

def S(p):
    tot = 0
    t = p - 1
    for i in range(1, 6):
        tot += t
        t = (mod_inv(p - i, p) * t) % p

    return tot % p

ans = sum(S(p) for p in primes)
print('Solution:', ans)

end = perf_counter()
print(end - start, 'seconds to run')

