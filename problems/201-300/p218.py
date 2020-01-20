from lib.utility import start_time, end_time, gcd
start_time()


def enumerate_primitive_triples(c_limit):
    for m in range(2, 1 + int(c_limit ** 0.5)):
        n_start = 1 if m % 2 == 0 else 2
        for n in range(n_start, m, 2):
            if gcd(m, n) != 1:
                continue

            a = m*m - n*n
            b = 2 * m * n
            c = m*m + n*n

            if c > c_limit:
                break

            if a > b:
                a, b = b, a

            yield (a, b, c)


count = 0
limit = 10 ** 16

for n, m, _ in enumerate_primitive_triples(limit ** 0.5):
    a = m*m - n*n
    b = 2 * m * n
    c = m*m + n*n

    if c > limit:
        continue

    area = (a * b) // 2
    if area % 6 == 0 and area % 28 == 0:
        continue
    count += 1

print('Solution:', count)
end_time()
