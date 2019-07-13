"""
A = (0, 0)
B = (c, 0)

C = (x, y) where
    x = (c^2 + b^2 - a^2) / 2c
    y = sqrt(b^2 - x^2)

O = (c / 2, -sqrt(3/4) * c)

p + q + r = CO = sqrt((c/2 - x)^2 + (sqrt(3/4)*c + y)^2)
"""
from lib.utility import start_time, end_time, multi_gcd
from lib.prime import read_primes
from math import sqrt
start_time()


def is_square(n):
    return round(sqrt(n)) ** 2 == n


def compute_pqr(a, b, c):
    x = a*a + b*b + c*c
    y = 12*(b*c)**2 - 3*(c*c + b*b - a*a)**2
    if not is_square(y):
        return None

    z = x + int(sqrt(y))
    if z % 2 != 0:
        return None

    z //= 2
    if not is_square(z):
        return None

    return int(sqrt(z))


# print(compute_pqr(399, 455, 511))

prime_set = set(read_primes(10000))

# c^2 = a^2 + b^2 + a*b


primitive = (57, 65, 73)

num_sols = 0
for c in range(4, 400):
    for b in range(1, c + 1):
        min_a = c - b + 1

        if is_square(4*c*c - 3*b*b):
            a = int(sqrt(4*c*c - 3*b*b)) - b
            if a % 2 == 0:
                a //= 2
                if a >= min_a and a <= b and multi_gcd(a, b, c) == 1:
                    res = compute_pqr(a, b, c)
                    # num_sols += 1

                    if res is not None:
                        # print(c, b, a, '|', res, '|', 'yeet')
                        # continue
                        pass

        for a in range(min_a, b + 1):
            if multi_gcd(a, b, c) != 1:
                continue

            res = compute_pqr(a, b, c)
            if res is not None:
                sol1 = c*c - (a*a + b*b + a*b)
                s = int(sqrt(-3*a**4 - 3*(b*b - c*c)**2 + 6*a**2 * (b*b + c*c)))

                num_sols += 1
                print(f'{{c->{c}, b->{b}, a->{a}, s->{s}}}', '|', res, '|', sol1,)
                print(f'a = {a}')
                print(f'b = {b}')
                print(f'c = {c}')
                print(f's = {s}')
                print('\n')


print('numsols:', num_sols)
print(compute_pqr(*primitive))


end_time()
