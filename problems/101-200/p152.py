from lib.utility import start_time, end_time, subsets
from fractions import Fraction
start_time()


nums = [Fraction(1, n) for n in range(2, 46)]
print(len(nums))
n = len(nums) // 2

# x = sorted([sum(s) for s in subsets(nums[:n])])
# y = sorted([sum(s) for s in subsets(nums[n:])])
# print(n)
print(nums[:n])
print(nums[n:])

end_time()
