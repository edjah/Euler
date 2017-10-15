from prime import miller_rabin
from time import perf_counter

start = perf_counter()

ans = 0
lim = 10 ** 14
def dfs(n, t):
    global ans
    if n >= lim // 10:
        return
    if n % t == 0:
        x = 10 * n
        if miller_rabin(n // t):
            for i in (1, 3, 7, 9):
                q = x + i
                if q < lim and miller_rabin(q):
                    ans += q
        for d in range(10):
            dfs(x + d, t + d)

for i in range(1, 10):
    dfs(i, i)

print('Solution:', ans)

end = perf_counter()
print(end - start, 'seconds to run')
