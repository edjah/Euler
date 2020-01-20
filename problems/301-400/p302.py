from lib.utility import start_time, end_time, multi_gcd, memoize
from lib import prime
from collections import defaultdict

limit = 10 ** 4
primes = prime.init(int(limit ** 0.5))

nums = set()

print(len(primes))

# def powerful(i, prod, has_odd_power, curr_power):
#     if i >= len(primes):
#         if prod < limit and has_odd_power:
#             nums.add(prod)
#         return
#     if prod >= limit:
#         return

#     # if has_odd_power:
#         # print(prod)

#     powerful(i + 1, prod, has_odd_power or curr_power % 2 == 1, 0)

#     if i < len(primes) - 1:
#         powerful(i + 1, prod * primes[i + 1] ** 2, has_odd_power or curr_power % 2 == 1, 2)

#     if curr_power != 0:
#         powerful(i, prod * primes[i], has_odd_power, curr_power + 1)


# powerful(-1, 1, False, 0)


start_time()


nums2 = {}


def test2():
    ops = 0

    assert primes == sorted(primes)
    lvls = [{}]
    for p in primes:
        z = p*p
        c = 2
        while z < limit:
            ops += 1
            nums2[z] += 1
            lvls[0][z] += 1
            c += 1
            z *= p

    while True:
        lvls.append({})
        for l, counts in lvls[-2].items():
            for p in primes:
                z = l*p

                if z >= limit:
                    break

                c = 1
                while z < limit:
                    ops += 1
                    nums2[z] = counts + (p, c)
                    lvls[-1][z] = counts + (p, c)
                    c += 1
                    z *= p

        if lvls[-1] == {}:
            break

    print([len(l) for l in lvls], sum(len(l) for l in lvls))
    print('test2 ops:', ops)


test2()

print('ayy:', len(nums2))
# new_nums = set()
# for n in nums:
#     from collections import Counter
#     if multi_gcd(*Counter(prime.prime_factors(n)).values()) == 1:
#         new_nums.add(n)

# nums = new_nums
# print(len(nums))

# count = 0
# for n in nums:
#     if prime.totient(n) in nums:
#         print(n, prime.totient(n))
#         count += 1

# print('count:', count)
end_time()
