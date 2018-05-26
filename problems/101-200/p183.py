from time import perf_counter
from math import e
start = perf_counter()

def is_terminating(num, den):
    while den % 2 == 0:
        den //= 2
    while den % 5 == 0:
        den //= 5
    return den == 1

def D(N):
    k = round(N / e)
    if is_terminating(N, k):
        return -N
    return N

ans = 0
for n in range(5, 10001):
    ans += D(n)

print('Solution:', ans)


end = perf_counter()
print(end - start, 'seconds to run')
