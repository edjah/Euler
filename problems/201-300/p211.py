from time import perf_counter
from lib.prime import read_primes
start = perf_counter()

def divisor_square_sum_tbl(n):
    tbl = [0] * (n + 1)
    for i in range(1, n + 1):
        for j in range(i, n + 1, i):
            tbl[j] += i * i
    return tbl

lim = 1 * 10 ** 6
squares = {i * i for i in range(int(lim ** 0.5) + 1)}

x = divisor_square_sum_tbl(lim)
for i in filter(lambda z: z[1] in squares, enumerate(x)):
    # print(i)
    pass


end = perf_counter()
print(end - start, 'seconds to run')
