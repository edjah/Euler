from time import perf_counter
import prime
from tqdm import tqdm
from multiprocessing import Pool
start = perf_counter()

primes = prime.init(1000030)[2:]

def connection(i):
    p1, p2 = primes[i], primes[i + 1]
    n = 10 ** len(str(p1))
    ans = p2
    while ans % n != p1:
        ans += p2
    return ans


pool = Pool(4)
solution = 0
for ans in tqdm(pool.imap_unordered(connection, range(len(primes) - 1), 20), total=len(primes) - 1):
    solution += ans
print('Solution:', solution)

end = perf_counter()
print(end - start, 'seconds to run')
