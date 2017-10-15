from time import perf_counter
from math import sqrt
start = perf_counter()

figurates = {
    3: lambda n: n * (n + 1) // 2,
    4: lambda n: n * n,
    5: lambda n: n * (3 * n - 1) // 2,
    6: lambda n: n * (2 * n - 1),
    7: lambda n: n * (5 * n - 3) // 2,
    8: lambda n: n * (3 * n - 2)
}

nums = []
for i in range(0, 200):
    for f in figurates:
        x = figurates[f](i)
        if x >= 1000 and x <= 9999:
            nums.append((x, f))
nums.sort()
indices = {nums[i][0] : i for i in range(len(nums))}


def cyclic_figurate_set(n):
    candidates = []
    def cyclic_rec(acc, n):
        if n <= 0:
            if acc[0][0] // 100 == acc[-1][0] % 100:
                s = set(x[1] for x in acc)
                if len(s) != len(acc):
                    return
                candidates.append([x[0] for x in acc])
            return
        elif acc == []:
            for x in nums:
                cyclic_rec([x], n - 1)
        else:
            k = acc[-1][0] % 100 * 100
            lim = k + 100
            while k not in indices and k < lim:
                k += 1
            if k not in indices:
                return
            i = indices[k]
            while i < len(nums) and nums[i][0] < lim:
                cyclic_rec(acc + [nums[i]], n - 1)
                i += 1
    cyclic_rec([], n)
    return candidates


candidates = cyclic_figurate_set(6)
for c in candidates:
    print(c, ':', sum(c))

end = perf_counter()
print(end - start, 'seconds to run')
