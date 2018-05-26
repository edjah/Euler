import time
from itertools import combinations
start = time.time()

def power_set(s):
    return [t for i in range(1, len(s) + 1) for t in combinations(s, i)]

def solve(n):
    ans = 0
    s = set(range(n))
    for u in power_set(s):
        for v in power_set(s - set(u)):
            if len(u) != len(v):
                continue
            if any(y < x for x, y in zip(*sorted([u, v]))):
                ans += 1

    return ans // 2

print("Solution:", solve(12))


end = time.time()
print(f"{end - start:.3f} sec")
