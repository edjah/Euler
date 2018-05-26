from time import perf_counter
from decimal import *
start = perf_counter()

getcontext().prec = 100
def s5000(r):
    n = -299 + 300*r - 4701*r**5000 + 4700*r**5001
    d = (r - 1) ** 2
    return -3 * n / d + 600000000000

def ds5000(r):
    n = -298 + 300*r - 23505000*r**4999 + 47000298*r**5000 - 23495300*r**5001
    d = (r - 1) ** 3
    return 3 * n / d

def newtons_method(f, df, guess, prec, trials):
    x = Decimal(guess)
    n = 0
    while abs(f(x)) > prec and n < trials:
        x = x - f(x)/df(x)
        n += 1
    return x

a = newtons_method(s5000, ds5000, 1.01, 1e-50, 1000)
print('Solution: %.12f' % a)
print('Closeness: %e' % s5000(a))

end = perf_counter()
print(end - start, 'seconds to run')
