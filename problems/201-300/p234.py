from lib.utility import start_time, end_time
from lib.prime import read_primes
start_time()

limit = 999966663333
primes = read_primes(int(limit ** 0.5) + 1000)

total = 0
for i in range(len(primes) - 1):
    # we look at numbers between a**2 and b**2
    a = primes[i]
    b = primes[i + 1]

    # add the semidivisible numbers that are divisible by a and not b
    start = a ** 2 + a
    for i in range(start, b ** 2, a):
        if i < limit and i % b != 0:
            total += i

    # add the semidivisible numbers that are divisible by b and not a
    start = (a ** 2 + b) - (a ** 2 + b) % b
    for i in range(start, b ** 2, b):
        if i < limit and i % a != 0:
            total += i

print('Solution:', total)
end_time()
