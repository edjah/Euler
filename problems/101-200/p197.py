import time
from math import floor
start = time.time()

def f(x):
    return floor(pow(2, 30.403243784 - x**2)) * pow(10, -9)

N = 10 ** 4
un = -1
for n in range(N):
    un = f(un)

print(un + f(un))

end = time.time()
print(f"{1000 * (end - start):.3f} ms")
