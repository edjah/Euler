from time import perf_counter
from multiprocessing import Pool
from tqdm import tqdm
start = perf_counter()

squares = {i * i for i in range(300)}

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def area(a, b, c, d):
    return (a + c) * (b + d)

def count(a, b, c, d):
    A = area(a, b, c, d)
    B = gcd(a, b) + gcd(a, d) + gcd(c, b) + gcd(c, d) - 4
    return A - (B // 2) + 1

m = 100
t = 0

def test(a):
    t = 0
    for b in range(1, m + 1):
        for c in range(1, m + 1):
            for d in range(1, m + 1):
                t += count(a, b, c, d) in squares
    return t

pool = Pool(4)
t = sum(tqdm(pool.imap_unordered(test, range(1, m + 1)), total=m))
sol = t - m
print('Solution:', sol)


end = perf_counter()
print(end - start, 'seconds to run')
