from lib.utility import start_time, end_time, product
from lib.prime import prime_factors_table
start_time()

factors = prime_factors_table(10 ** 5)
a = [(n, product(set(factors[n]))) for n in range(0, 10 ** 5 + 1)]
E = sorted(a, key=lambda x: (x[1], x[0]))
print('Solution:', E[10000][0])

end_time()
