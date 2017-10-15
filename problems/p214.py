from time import perf_counter
import prime
start = perf_counter()


primes = prime.read_primes(40 * 10 ** 6)
prime_set = set(primes)
totient = prime.totient_table(40 * 10 ** 6)

t_gen = perf_counter() - start
print('Done creating totient table.', t_gen, 'seconds')

cache = {}
def chain(n):
    if n in cache:
        return cache[n]
    elif n == 1:
        return 1
    elif n in prime_set:
        ans = 1 + chain(n - 1)
    else:
        ans = 1 + chain(totient[n])

    cache[n] = ans
    return ans

tot = 0
num = 0
for p in primes:
    if chain(p) == 25:
        num += 1
        tot += p

print('Number:', num)
print('Solution:', tot)



end = perf_counter()
print(end - start, 'seconds to run')
