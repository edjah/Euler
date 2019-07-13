from lib.utility import start_time, end_time, product
from lib.prime import prime_factors_table
start_time()

"""
(x + y) / (xy) = 1/n
nx + ny = xy
nx + ny - xy = 0
y(n - x) = -nx

y = nx / (x - n)
y = (n^2 - n^2 + nx) / (x - n)
y = (n^2 + n(x - n)) / (x - n)
y = n^2 / (x - n) + n
=> All solutions must have x - n as a divisor of n^2
=> Count the number of divisors of n^2
"""


def num_solutions(n):
    uniq = set(prime_factors[n])
    exponents = [2 * prime_factors[n].count(x) for x in uniq]
    num_divisors = product(1 + exp for exp in exponents)
    return (num_divisors + 1) // 2


prime_factors = prime_factors_table(10 ** 6)

n = 0
while num_solutions(n) <= 1000:
    n += 1

print('Solution:', n)
end_time()
