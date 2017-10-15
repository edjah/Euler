from time import perf_counter
start = perf_counter()

def close_to_int(a):
    return abs(round(a) - a) < 1e-8


def diophantine_reciprocal_count(n):
    count = 0
    for i in range(n + 1, 2*n + 1):
        if close_to_int(1/(1/n - 1/i)):
            count += 1
    return count

from prime import read_primes

# n = 1
# m = (0, 0)
# a = diophantine_reciprocal_count(n)
# while a <= 1000:
#     if n % 100 == 0:
#         print('%d: current max:' % n, m[0], '@', m[1])
#         print(prime.prime_factors(m[1]),'\n\n')

#     n += 1
#     a = diophantine_reciprocal_count(n)
#     if a > m[0]:
#         m = (a, n)
# print(n, ':', a)

def g_hamming_nums(lim, n):
    primes = read_primes(n)
    nums = set()
    seen = set()
    def helper(k, idx):
        if k > lim or idx >= len(primes):
            return
        nums.add(k)
        helper(k * primes[idx], idx)
        helper(k * primes[idx], idx + 1)
    helper(1, 0)
    return sorted(nums)

nums = g_hamming_nums(10 ** 6, 100)
print(len(nums))
m = (0, 0)
for i, n in enumerate(nums):
    if i % 100 == 0:
        print('%d: %d = max: %d @ %d' % (i, n, m[0], m[1]))
    a = diophantine_reciprocal_count(n)
    if a > 1000:
        print('Solution:', n)
        break
    if a > m[0]:
        m = (a, n)

end = perf_counter()
print(end - start, 'seconds to run')
