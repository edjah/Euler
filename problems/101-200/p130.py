from time import perf_counter
start = perf_counter()

import lib.prime as prime
primes = prime.init(10 ** 3)

def R(k):
    return int('1' * k)

max_k = 0
def A(n):
    global max_k
    if n % 2 == 0 or n % 5 == 0:
        return None
    k = 1
    while R(k) % n != 0:
        k += 1
    return k

for i in range(3, 101):
    if i % 2 == 0 or i % 5 == 0:
        continue
    if i not in primes:
        print('%d: %d' % (i, A(i)))

# semiprimes = []
# for i in range(len(primes) - 1):
#     for j in range(i + 1, len(primes)):
#         a, b = primes[i], primes[j]
#         if a in (2, 5) or b in (2, 5):
#             continue
#         semiprimes.append(a * b)

# semiprimes = sorted(semiprimes)
# nums = []
# for p in semiprimes:
#     if (p - 1) % A(p)  == 0:
#         print(p)
#         nums.append(p)
#     if len(nums) >= 25:
#         break

# print(nums)
# print('Solution:', sum(nums))


end = perf_counter()
print(end - start, 'seconds to run')
