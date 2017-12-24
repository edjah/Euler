from time import perf_counter
import prime
start = perf_counter()

prime.init(10 ** 5)


def divisors(n):
    nums = []
    for i in range(1, int(n ** 0.5) + 1):
        if n % i == 0:
            nums.extend([i, n // i])

    return sorted(set(nums))


cache = {}

def repunit_primes(n):
    if n == 1:
        return []
    if n in cache:
        return cache[n]


    ans = []
    repunit = (10 ** n - 1) // 9
    print(repunit)
    for d in divisors(n):
        if d != n:
            for m in repunit_primes(d):
                print(m)
                if repunit % m == 0:
                    ans.append(m)
                    repunit //= m

    ans.extend(prime.prime_factors(repunit))

    cache[n] = ans
    return ans


s = repunit_primes(4)
print(s)


end = perf_counter()
print(f"{end - start:f} seconds to run")
