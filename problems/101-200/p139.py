from lib.utility import start_time, end_time, gcd
start_time()


def enumerate_primitive_triples(perim_limit):
    for m in range(2, 1 + int(perim_limit ** 0.5)):
        n_start = 1 if m % 2 == 0 else 2
        for n in range(n_start, m, 2):
            if gcd(m, n) != 1:
                continue

            a = m*m - n*n
            b = 2 * m * n
            c = m*m + n*n

            if a + b + c >= perim_limit:
                break

            if a > b:
                a, b = b, a

            yield (a, b, c)


def can_tile(a, b, c, perim_limit):
    if c % (b - a) == 0:
        return (perim_limit - 1) // (a + b + c)
    return 0


ans = 0
perim_limit = 10 ** 8
for a, b, c in enumerate_primitive_triples(perim_limit):
    ans += can_tile(a, b, c, perim_limit)

print('Solution:', ans)
end_time()
