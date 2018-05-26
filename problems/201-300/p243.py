from time import perf_counter
import lib.prime as prime

prime.init(30)
primes = prime.prime_list
start = perf_counter()

def resilience(k, lim):
    nums = []
    seen = set()
    def candidates(n):
        if n > lim or n in seen:
            return
        seen.add(n)
        nums.append(n)
        for i in primes:
            if n * i > lim:
                break
            candidates(n * i)
    candidates(1)
    nums.remove(1)
    nums.sort()

    for i in nums:
        n = prime.totient(i)
        if n/(i - 1) < k:
            print('Found solution!')
            break
    return i

solution = resilience(15499/94744, 10 ** 9)
print(prime.prime_factors(solution))
print('Solution:', solution)

end = perf_counter()
print(end - start, 'seconds to run')
