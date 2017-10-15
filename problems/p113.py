from time import perf_counter, sleep
from math import factorial
start = perf_counter()


nd_cache = {}
def non_decreasing(a, b):
    if (a, b) in nd_cache:
        return nd_cache[(a, b)]
    if b <= 0:
        return 1
    c = 0
    for i in range(a, 10):
        c += non_decreasing(i, b - 1)

    nd_cache[(a, b)] = c
    return c


def non_increasing(a, b):
    c = 0
    for i in range(0, a + 1):
        c += non_decreasing(i, b - 1)
    return c

t = 0
for d in range(1, 100001):
    t += non_increasing(9, d) - 9
    t += non_decreasing(1, d) - 1

print(t)

end = perf_counter()
print(end - start, 'seconds to run')
