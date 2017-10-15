from time import clock
from random import random
from utility import *
start = clock()


def approximation(trials):
    def test():
        urns = [10] * 7
        selected = set()
        remaining = 70
        for _ in range(20):
            r = random()
            for i in range(7):
                k = urns[i]/remaining
                if k > r:
                    urns[i] -= 1
                    selected.add(i)
                    break
                else:
                    r -= k
            remaining -= 1
        return len(selected)

    tot_distinct = 0
    dist = [0] * 8
    for trial in range(trials):
        a = test()
        dist[a] += 1
        tot_distinct += a
    tot_distinct /= trials
    print('Distribution\n------------')
    for i in range(1, 8):
        print('%d: %f' % (i, dist[i]/trials))
    print('\nAvg:', tot_distinct, end='\n'*2)

approximation(1) #6.81789

def fac_prod(n, d, k):
    prod = 1
    for i in range(k):
        prod *= (n - i)/(d - i)
    return prod

print(fac_prod(10, 70, 10))



end = clock()
print(end - start, 'seconds to run')

t = 1
for i in range(20):
    t *= 70 - i
print(t * nCr(70, 20))
"""
Distribution
------------
1: 0.000000
2: 0.000000
3: 0.000000
4: 0.000010
5: 0.006110
6: 0.168980
7: 0.824900
"""
