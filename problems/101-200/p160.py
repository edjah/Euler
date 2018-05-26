from time import perf_counter
from math import factorial
start = perf_counter()

def count_zeros(n):
    c, t = 0, 5
    while t <= n:
        c += n // t
        t *= 5
    return c

def naive(n):
    fac = factorial(n)
    zeros = count_zeros(n)
    return (fac // 10 ** zeros) % (10 ** 5)

def alternative(n):
    c = 1
    for i in range(1, n + 1):
        c *= i
        if i % 5 == 0:
            while i % 5 == 0:
                c //= 10
                i //= 5

    return c % (10 ** 5)

for i in range(1, 100):
    print('%d: %d vs %d' % (i, naive(i), alternative(i)))

goal = 10 ** 12
print(count_zeros(goal))

end = perf_counter()
print(end - start, 'seconds to run')
