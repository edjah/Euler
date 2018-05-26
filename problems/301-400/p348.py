from time import perf_counter
from itertools import permutations
start = perf_counter()

d = {}
count = 0
nums = []
for s in range(1, 40000):
    for c in range(1, 5000):
        n = s**2 + c**3
        a = str(n)
        if a == a[::-1]:
            if n in d:
                d[n] += 1
                if d[n] == 4:
                    count += 1
                    nums.append(n)

            else:
                d[n] = 1

print(nums)
a = sorted(d, key=lambda x: d[x], reverse=True)[:10]
for i in a:
    print(i, d[i])

print('Solution:', sum(nums))




end = perf_counter()
print('%f seconds to run' % (end - start))
