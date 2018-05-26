from time import perf_counter
from random import random
from math import log, e
start = perf_counter()

f=lambda x:x

n = 10
p = 3
def f(x):
    a = 0
    while x%p==0:
        a += 1
        x//=p
    return a

print(sum(f(i) for i in range(2,n+1)))

end = perf_counter()
print(end - start, 'seconds to run')
