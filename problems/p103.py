from time import perf_counter
from itertools import combinations
start = perf_counter()

def power_set(s):
    a = []
    for n in range(len(s) + 1):
        for x in combinations(s, n):
            a.append(set(x))
    return a

def works(s):
    if len(set(s)) != len(s):
        return False
    s = set(s)
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



def optimum(prev, n):
    b = prev[len(prev) // 2]
    best = (b, *(a + b for a in prev))
    seen = set()
    def optimize(s, idx):
        if (s, idx) in seen:
            return
        nonlocal best
        if idx >= n:
            if works(s) and sum(s) < sum(best):
                best = s
            return

        seen.add((s, idx))
        a = list(s)
        for i in range(-4, 4):
            a[idx] -= i
            optimize(tuple(sorted(a)), idx + 1)

    optimize(best, 0)
    print('Best sum:', sum(best))
    return sorted(best)

a = optimum([11, 18, 19, 20, 22, 25], 7)
print(a)
print('Solution:', ''.join(str(i) for i in a))


end = perf_counter()
print(end - start, 'seconds to run')
