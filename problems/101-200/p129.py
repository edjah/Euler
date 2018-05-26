from time import perf_counter
import lib.prime as prime
primes = set(prime.init(10 ** 5))

start = perf_counter()

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a


def A(n):
    k = 1
    repunit = 1

    while repunit % n != 0:
        repunit = 10 * repunit + 1
        k += 1

    return k

def test(n):
    pass

for i in range(10, 10 ** 3 + 1):
    if i % 2 > 0 and i % 5 > 0:
        ai = A(i)
        # msg = ' (gucci)' if ai == i - 1 else ''
        msg = ''
        if i == ai + 1:
            # assert(i in primes)
            # print('{}{}: {}'.format(i, msg, ai, test(i)), prime.prime_factors(ai))
            print(i, end=',')


end = perf_counter()
print(end - start, 'seconds to run')
