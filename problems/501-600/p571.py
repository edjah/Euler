from time import perf_counter
from itertools import permutations
start = perf_counter()

numerals = "0123456789abcdefghijklmnopqrstuvwxyz"
def baseN(n, b):
    if n == 0:
        return numerals[0]
    else:
        return baseN(n // b, b).lstrip(numerals[0]) + numerals[n % b]


def pandigital(n, b):
    return set(numerals[:b]) == set(baseN(n, b))

nums = []
base = 12
perm = permutations(numerals[:base])
while len(nums) < 10:
    n = next(perm)
    if n[0] == '0':
        continue
    n = int(''.join(n), base)
    if all(pandigital(n, b) for b in range(2, base + 1)):
        print('YAY!:', n)
        nums.append(n)

print(nums)
print('Solution:', sum(nums))


end = perf_counter()
print('%f seconds to run' % (end - start))
