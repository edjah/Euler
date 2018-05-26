from time import perf_counter
from random import randint
from math import e
start = perf_counter()

def simulate(f):
    cash = 1
    for i in range(1000):
        if randint(0, 1) == 1:
            cash *= 1 + 2 * f
        else:
            cash *= 1 - f
    return cash

# km
def median_median(f, trials=100):
    z = []
    for a in range(trials):
        t = []
        for i in range(trials):
            t += [simulate(f)]
        z += [sorted(t)[trials//2]]
    return sorted(z)[trials//2]

# print(1/(e*e))
a = median_median(0.25, 30)
print(a)


end = perf_counter()
print(end - start, 'seconds to run')
