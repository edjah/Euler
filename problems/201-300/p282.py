from lib.utility import start_time, end_time, egcd, product
from lib import prime
start_time()

prime.init(10 ** 3)


def up_arrow(a, num_arrows, b, mod):
    # currently assumes that a == 2
    assert a == 2

    if num_arrows == 1:
        return pow(a, b, mod)
    if b == 0:
        return 1
    if mod == 1:
        return 0

    # decompose the modulus into two co-prime components
    factors = prime.prime_factors(mod)
    mod1 = 2 ** factors.count(2)
    mod2 = product(p for p in factors if p != 2)

    # compute the result % mod1. we hardcode these results
    if b == 1:
        res1 = 2 % mod1
    elif b == 2:
        res1 = 4 % mod1
    elif num_arrows == 2 and b == 3:
        res1 = 16 % mod1
    else:
        # the result is some power of two that's >= 65536 = 2^16
        # so, it should always be equal to 0 if the modulus is a power of 2
        # that's <= 2^16
        assert factors.count(2) <= 16
        res1 = 0

    # compute the result % mod2. use euler's theorem
    phi = prime.totient(mod2)
    tmp = up_arrow(a, num_arrows, b - 1, phi)
    res2 = up_arrow(a, num_arrows - 1, tmp, mod2)

    # apply the chinese remainder theorem to compute the final result
    d, x, y = egcd(mod1, mod2)
    return (res1*y*mod2 + res2*x*mod1) % (mod1 * mod2)


def ack(m, n, mod):
    if m == 0:
        res = n + 1
    elif m == 1:
        res = n + 2
    elif m == 2:
        res = 2*n + 3
    else:
        res = up_arrow(2, m - 2, n + 3, mod) - 3

    return res % mod


mod = 14 ** 8
tot = 0
for n in range(7):
    tot += ack(n, n, mod)


print('Solution:', tot % mod)
end_time()
