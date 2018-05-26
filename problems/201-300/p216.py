from time import perf_counter
from multiprocessing import Pool
from tqdm import tqdm
start = perf_counter()


miller_rabin_nums = [2, 3, 5, 7, 11, 13, 17]
large_miller_rabin_nums = [19, 23, 29, 31, 37, 41]
def miller_rabin(n, k=25):
    if n == 2 or n == 3:
        return True
    if n % 2 == 0 or n < 2:
        return False

    s = 0
    d = n - 1
    while d % 2 == 0:
        d //= 2
        s += 1

    def try_composite(a):
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            return False
        for i in range(s):
            if x == n - 1:
                return False
            x = pow(x, 2, n)
        return True

    for i in miller_rabin_nums:
        if i != n and try_composite(i):
            return False

    if n >= 341550071728321:
        for i in large_miller_rabin_nums:
            if try_composite(i):
                return False
    return True

def test(n):
    return miller_rabin(2*n*n - 1)

pool = Pool(64)
N = 5 * 10 ** 7
sol = sum(tqdm(pool.imap_unordered(test, range(N), 100), total=N))

print('Solution:', sol)

end = perf_counter()
print('Finished in %f seconds' % (end - start))
