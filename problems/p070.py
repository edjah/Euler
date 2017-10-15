from time import perf_counter
from prime import totient_table
from collections import Counter

start = perf_counter()

def is_perm(a, b):
    return sorted(str(a)) == sorted(str(b))

def min_totient_perm(n):
    t = totient_table(n)
    best = (None, float('inf'))
    for i in range(2, n + 1):
        if is_perm(i, t[i]):
            x = i / t[i]
            if x < best[1]:
                best = (i, x)
    return best

print('Solution:', min_totient_perm(10 ** 7))

end = perf_counter()
print(end - start, 'seconds to run')
