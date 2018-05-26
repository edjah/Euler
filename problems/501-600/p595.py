from time import perf_counter
from math import factorial
start = perf_counter()

from lib.utility import nCr
from math import factorial

acache = {}
def a(n):
    if n in acache:
        return acache[n]
    if n == 0:
        return 1
    elif n == 1:
        return 1
    ans =  n * a(n-1) + (n-1) * a(n-2)
    acache[n] = ans
    return ans

cache = {}
def S(n):
    if n in cache:
        return cache[n]
    if n <= 1:
        return -1
    t = 0
    for k in range(1, n):
        t += S(k) * a(k - 1) * nCr(n - 1, k - 1)
    t = 1 + t/factorial(n)
    z = a(n - 1)/factorial(n)
    t *= 1/(1 - z)
    cache[n] = t
    return t

print('Solution: %0.8f' % S(52))

end = perf_counter()
print(end - start, 'seconds to run')
