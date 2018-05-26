from time import perf_counter
from itertools import combinations
start = perf_counter()

def power_set(s):
    a = []
    for n in range(1, len(s) + 1):
        for x in combinations(s, n):
            a.append(set(x))
    return a

def is_special(s):
    subsets = power_set(s)
    for x in subsets:
        for y in power_set(s - x):
            if len(x) == len(y) == 0:
                continue
            a, b = sum(x), sum(y)
            if len(x) < len(y) and a >= b:
                return False
            if len(y) < len(x) and b >= a:
                return False
            if a == b:
                return False
    return True

sets = []
with open('p105_sets.txt', 'r') as f:
    for line in f:
        sets.append(set(int(i) for i in line.split(',')))

ans = sum(sum(i) for i in filter(is_special, sets))
print('Solution:', ans)

end = perf_counter()
print(end - start, 'seconds to run')
