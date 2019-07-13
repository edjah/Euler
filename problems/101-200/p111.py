from lib.utility import start_time, end_time
from lib.prime import miller_rabin
from itertools import combinations, product
start_time()


def find_primes_with_runs(n, d):
    replacement_digits = [str(i) for i in range(10) if i != d]
    ans = []

    for r in range(1, n - 1):
        for idx in combinations(range(n), r):
            s = [str(d)] * n
            for dig in product(replacement_digits, repeat=r):
                for i in range(r):
                    s[idx[i]] = dig[i]

                if s[0] != '0':
                    x = int(''.join(s))
                    if miller_rabin(x):
                        ans.append(x)

        if len(ans) > 0:
            return ans

    return ans


tot = 0
for d in range(10):
    primes = find_primes_with_runs(10, d)
    m = str(primes[0]).count(str(d))
    n = len(primes)
    s = sum(primes)
    print(f'Dig: {d} | M: {m} | N: {n:>2} | S: {s}')
    tot += s

print('Solution:', tot)
end_time()
