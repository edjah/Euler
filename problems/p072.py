from time import perf_counter
from prime import totient_table

start = perf_counter()

def proper_fraction_count(n):
    return sum(totient_table(n)) - 1

print('Solution:', proper_fraction_count(10 ** 6))

end = perf_counter()
print(end - start, 'seconds to run')
