from lib.utility import start_time, end_time
from lib.prime import read_primes
start_time()

prime_set = set(read_primes(10 ** 6))


def A(n):
    k = 1
    repunit = 1

    while repunit != 0:
        repunit = (10 * repunit + 1) % n
        k += 1

    return k


n = 91
composites = []
while len(composites) < 25:
    if n % 2 != 0 and n % 5 != 0 and n not in prime_set:
        if (n - 1) % A(n) == 0:
            composites.append(n)
    n += 1

print('Solution:', sum(composites))
end_time()
