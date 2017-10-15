from time import perf_counter
from prime import miller_rabin
start = perf_counter()

valid_incr = {1, 3, 7, 9, 13, 27}

def ensure(n):
    k = n * n
    for i in valid_incr:
        if not miller_rabin(k + i):
            return False
    return True

def consec_ensure(n):
    k = n * n
    for i in range(1, 28, 2):
        if miller_rabin(k + i) ^ (i in valid_incr):
            return False
    return True

t = 0
for n in range(10, 150 * 10 ** 6, 10):
    if n % 210 not in {10, 80, 130, 200}:
        continue

    if ensure(n) and consec_ensure(n):
        print(n)
        t += n

print('Solution:', t)

end = perf_counter()
print(end - start, 'seconds to run')
