import time
from lib.prime import miller_rabin
start = time.time()

ans = 0
lim = 10 ** 14
def dfs(n, t):
    if n >= lim // 10:
        return 0

    ans = 0
    if n % t == 0:
        x = 10 * n
        if miller_rabin(n // t):
            for i in (1, 3, 7, 9):
                q = x + i
                if q < lim and miller_rabin(q):
                    ans += q
        for d in range(10):
            ans += dfs(x + d, t + d)

    return ans

ans = 0
for i in range(1, 10):
    ans += dfs(i, i)

print('Solution:', ans)

end = time.time()
print(f"{1000 * (end - start):.3f} ms")
