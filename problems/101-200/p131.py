from time import perf_counter
from lib.prime import miller_rabin
start = perf_counter()

N = 10 ** 6
ans = k = p = 0
while p <= N:
    p = 3*k**2 + 3*k + 1
    ans += miller_rabin(p)
    k += 1

print('Solution:', ans)

end = perf_counter()
print(end - start, 'seconds to run')
