from lib.utility import start_time, end_time, mod_inverse
from lib.prime import read_primes
start_time()

primes = read_primes(1000030)[2:]


def connection(i):
    p1, p2 = primes[i], primes[i + 1]
    n = 10 ** len(str(p1))

    # computing a multiplier such that multiplier * p2 == 1 (mod n)
    multiplier = mod_inverse(p2, n)

    # modifying the multiplier so that (p1 * multiplier) * p2 == p1 (mod n)
    multiplier = (p1 * multiplier) % n
    return multiplier * p2


solution = 0
for i in range(len(primes) - 1):
    solution += connection(i)

print('Solution:', solution)
end_time()
