from time import perf_counter
import lib.prime as prime
start = perf_counter()

limit = 10 ** 2
nums = [1 + x for x in prime.init(limit)]
nset = set(nums)


# a*c == b*b

max_steps = 0
def find_all(b):
    target = nums[b] ** 2
    sols = []

    if b < len(nums) - b:
        for a in range(b):

            if target % nums[a] == 0 and (target // nums[a]) in nset:
                sols.append((nums[a] - 1, nums[b] - 1, target // nums[a] - 1))
    else:
        for c in range(b + 1, len(nums)):
            if target % nums[c] == 0 and (target // nums[c]) in nset:
                sols.append((target // nums[c] - 1, nums[b] - 1, nums[c] - 1))

    return sols

ans = 0
for i in range(len(nums)):
    for tup in find_all(i):
        tup[1] == 11 and print(tup)
        ans += sum(tup)

print("Solution:", ans)
print(max_steps)
print('Len nums:', len(nums))

end = perf_counter()
print(f"{end - start:.3f} sec")

