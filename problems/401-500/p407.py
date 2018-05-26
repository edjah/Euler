from time import perf_counter
import lib.prime as prime

start = perf_counter()
tbl = prime.prime_factors_table(10 ** 5)


def f(n):
    return tbl[n]


def M(n):
    for a in reversed(range(n)):
        if (a * a) % n == a:
            x, y, z = f(a), f(a - 1), f(n)
            if len(set(z)) > 1:
                m1, m2 = z[-2:]
                # print(x, y, z, sep=" | ")
                # assert (m1 in x and m2 in x) or (m1 in y and m2 in y)
            return a

# TODO: generative approach. list the numbers `a` from 1 to 10^7.
# find the prime factors for each .
# find the smallest number `n` such that `n > a` and `n` is built from the factors of `a` and `a - 1`


def g(a):
    facs = sorted(tbl[a] + tbl[a - 1])

    best = float('inf')

    def rec(n, idx):
        nonlocal best
        if idx == len(facs):
            return
        if n > a:
            best = min(best, n)
        rec(n, idx + 1)
        rec(n * facs[idx], idx + 1)

    rec(1, 0)
    return best

for i in range(1, 10 ** 4):
    # print(i, ':', g(i), '|', M(i))
    g(i)

print(16**2 % 24)

t = 0
for n in range(1, 10 ** 2 + 1):
    t += M(n)

print(t)


end = perf_counter()
print(f"{1000 * (end - start):.3f} ms")
