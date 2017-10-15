from time import perf_counter
import prime
start = perf_counter()

prime.init(10 ** 5)
fac = prime.prime_factors

# looking for d such that d * d = (n // d) * (n % d)
def is_progressive(n):
    for d in range(1, int(n ** 0.5) + 1):
        q = n // d
        r = n % d
        if d * d == q * r:
            print('%d: (d=%d, q=%d, r=%d)' % (n, d, q, r))
            print('n =', fac(n), ' | d =', fac(d),end='\n\n')
            return True
    return False

tot = 0
lim = 10 ** 6
for i in range(1, int(lim ** 0.5) + 1):
    n = i * i
    if is_progressive(n):
        tot += n


print('Solution:', tot, 'vs', 124657)


end = perf_counter()
print(end - start, 'seconds to run')
