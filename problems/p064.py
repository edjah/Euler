"""
Mathematica One-Liner
---------------------
Sum[x = ContinuedFraction[Sqrt[n]]; If[Length[x] == 1, 0, Mod[Length[x[[2]]], 2]], {n, 2, 10000}]
"""
from decimal import *
from time import clock
from math import sqrt
import math

start = clock()

getcontext().prec = 400

def cont_frac(n, rnd):
    if n == int(n):
        return (int(n), [])
    terms = []
    seen = set()
    while round(n, rnd) not in seen:
        seen.add(round(n, rnd))
        terms.append(int(n))
        n = 1 / (n - int(n))

    return (terms[0], terms[1:])

count = 0
total_len = 0
max_len = max_len_num = 0
for i in range(2, 10000 + 1):
    a, b = cont_frac(Decimal(i).sqrt(), 100)
    total_len += len(b)
    if len(b) > max_len:
        max_len = len(b)
        max_len_num = i
    count += len(b) % 2

print('Average length:', total_len/(10000 - 2))
print('Max_length:', max_len, 'at', max_len_num)
print('Solution:', count)

end = clock()
print(end - start, 'seconds to run')
