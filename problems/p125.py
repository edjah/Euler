from time import perf_counter
from random import randint

def palindromic(n):
    s = str(n)
    return s == s[::-1]


start = perf_counter()
lim = 10 ** 8
n = int(lim ** 0.5) + 1
a = set()
for s in range(1, n):
    t = s ** 2
    for i in range(s + 1, n):
        t += i ** 2
        if t > lim:
            break
        if palindromic(t):
            a.add(t)

print('Solution:', sum(a))


end = perf_counter()
print(end - start, 'seconds to run')
