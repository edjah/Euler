from time import perf_counter
from fractions import Fraction
from lib.utility import memoize
start = perf_counter()

limit = 35
nums = [Fraction(1, n ** 2) for n in range(2, limit + 1)]
sums = nums[:]
for i in reversed(range(len(nums))):
    if i < len(nums) - 1:
        sums[i] += sums[i + 1]

path = []

@memoize
def dfs(idx, tot):
    if tot == 0:
        print(path)
        return 1

    if idx >= len(nums) or tot > sums[idx]:
        return 0

    ans = dfs(idx + 1, tot)
    if tot - nums[idx] >= 0:
        path.append(nums[idx])
        ans += dfs(idx + 1, tot - nums[idx])
        path.pop()

    return ans


ans = dfs(0, Fraction(1, 2))
print(ans)

end = perf_counter()
print(f"{end - start:.3f} sec")
