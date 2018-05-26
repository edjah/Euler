from time import perf_counter
from math import log2
from matplotlib import pyplot as plt
start = perf_counter()


lim = 10 ** 8
k = int(log2(lim))
nums = [2 ** i for i in reversed(range(k + 1))]
print(nums)

cache = {}
t = 0
def D(n, i):
    global t
    t += 1
    tup = (n, i)
    if tup in cache:
        return cache[tup]
    if n == 0:
        return 1
    elif n < 0 or i >= len(nums):
        return 0
    tot = D(n, i + 1) + D(n - nums[i], i + 1) + D(n - 2 * nums[i], i + 1)
    cache[tup] = tot
    return tot

sols = []
for i in [10**a for a in range(6)]:
    sols.append((i, D(i, 0)))

for i in range(1, len(sols)):
    print(sols[i], sols[i][1] - sols[i - 1][1])

print('Iterations:', t)
print('Cache size:', len(cache))

end = perf_counter()
print(end - start, 'seconds to run')
