from lib.utility import start_time, end_time, subsets, product
from lib.prime import read_primes
start_time()


primes = read_primes(190)
prods1 = [product(p) for p in subsets(primes[:len(primes) // 2])]
prods2 = [product(p) for p in subsets(primes[len(primes) // 2:])]

prods1.sort()
prods2.sort()
sqrt = product(primes) ** 0.5

i = 0
j = len(prods2) - 1
best = 0

while i < len(prods1) and j >= 0:
    current = prods1[i] * prods2[j]
    if current >= sqrt:
        best = min(current, best)
        j -= 1
    elif current < sqrt:
        best = max(current, best)
        i += 1

print('Solution:', best % (10 ** 16))
end_time()
