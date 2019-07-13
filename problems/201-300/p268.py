from lib.utility import start_time, end_time
from lib.prime import read_primes
from bisect import bisect_left
start_time()

primes = read_primes(100)
# limit = 10 ** 16
import random
# limit = random.randint(1000, 10 ** 5)
limit = 43268
# limit = 10 ** 16
print('limit=', limit)
v1 = set()
v2 = set()


def version_100_iq(limit):
    nums = []
    for x in range(2, limit):
        facs = 0
        n = x
        for p in primes:
            if n % p == 0:
                facs += 1

                while n % p == 0:
                    n //= p

                if n == 1 or facs >= 4:
                    break

        if facs >= 4:
            nums.append(x)

    return set(nums)


def version_1(limit):
    def search(prod, i, num_distinct):
        if prod >= limit or i >= len(primes):
            return 0

        if prod not in v1 and num_distinct >= 4:
            v1.add(prod)

        not_used = (prod % primes[i] != 0)
        count = (num_distinct >= 4) and not not_used
        count += search(prod * primes[i], i, num_distinct + not_used)
        count += search(prod, i + 1, num_distinct)
        return count

    return search(1, 0, 0)


def version_2(limit):
    def search(prod, i, num_distinct):
        if prod >= limit:
            return

        if prod not in v1 and num_distinct >= 4:
            v1.add(prod)

        if i >= len(primes):
            return

        search(prod * primes[i], i + 1, num_distinct + 1)
        search(prod, i + 1, num_distinct)

    return search(1, 0, 0)


def find_prods_by_num_distinct_primes(limit, primes):
    prods_by_num_distinct = [set() for _ in range(5)]
    prods_by_num_distinct[0] |= {1}

    def add_prods(prod, i, num_distinct):
        if prod >= limit or i >= len(primes):
            return

        # not_used = (prod % primes[i] != 0)
        # if not not_used:
        prods_by_num_distinct[min(num_distinct, 4)].add(prod)

        add_prods(prod * primes[i], i + 1, num_distinct + 1)
        add_prods(prod, i + 1, num_distinct)

    add_prods(1, 0, 0)
    return [sorted(s) for s in prods_by_num_distinct]


version_2(limit)

pset = set(primes)

res = set()
count = 0
for n in sorted(v1):
    for mult in range(1, 401):
        if mult * n >= limit:
            break
        # if n % mult != 0 and mult in pset:
        if mult in pset:
            # assert(n * mult in v1), (n, mult)
            continue


        # print(n, mult)
        if n * mult in res:
            print(n, mult, n * mult)
        res.add(n * mult)
        count += 1
    else:
        print('not enough huh...', n)
        count += (limit - 100*n) // n


print(len(res))
# n = 7  # a splitting point that seems to be the fastest
# lo = find_prods_by_num_distinct_primes(limit, primes[:n])
# hi = find_prods_by_num_distinct_primes(limit, primes[n:])


# max_sol = 0
# count = 0
# for lo_num_distinct_primes in range(0, 5):
#     for prod in lo[lo_num_distinct_primes]:
#         for hi_num_distinct_primes in range(4 - lo_num_distinct_primes, 5):
#             # count += bisect_left(hi[hi_num_distinct_primes], limit / prod)
#             for v in hi[hi_num_distinct_primes]:
#                 if v * prod < limit:
#                     count += 1
#                     # count += (limit - 1) // (v * prod)


print('Solution:', count)

iq_100 = version_100_iq(limit)
print('100 IQ version:', len(iq_100))

# if count != len(iq_100):
    # print(iq_100 - v1)
# assert count == len(iq_100)



end_time()
