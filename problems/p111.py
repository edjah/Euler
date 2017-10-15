from time import perf_counter
from prime import miller_rabin
from itertools import combinations, product
start = perf_counter()

def A(n, d):
    orig = [str(d)] * n
    str_digits = [str(c) for c in range(10)]
    ans = []

    for r in range(1, n - 1):
        for idx in combinations(range(n), r):
            s = orig[:]
            for dig in product(str_digits, repeat=r):
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
    x = A(10, d)
    m = str(x[0]).count(str(d))
    n = len(x)
    s = sum(x)
    print('Dig: %d | M: %2d | N: %2d | S: %d'%(d,m,n,s))
    tot += s

print('Solution:', tot)
end = perf_counter()
print(end - start, 'seconds to run')
