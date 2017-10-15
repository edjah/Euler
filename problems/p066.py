from time import perf_counter
from math import ceil
start = perf_counter()

def compose(a, b, N):
    x1, y1, k1 = a
    x2, y2, k2 = b
    return (x1*x2 + N*y1*y2, x1*y2 + x2*y1, k1*k2)

def dsolve(N):
    a, b = ceil(N ** 0.5), 1
    k = a ** 2 - N
    while k != 1:
        best_m = (1, float('inf'), ())
        m = 1
        while True:
            t = compose((a, b, k), (m, 1, m**2 - N), N)
            if t[1] % k == 0:
                if abs(t[2]) < best_m[1]:
                    best_m = (m, abs(t[2]), t)
                elif abs(t[2]) > best_m[1]:
                    break
            m += 1
        t = best_m[2]
        a, b, k = abs(t[0]//k), abs(t[1]//k), t[2]//(k * k)
    return (a, b)

def is_square(n):
    k = n ** 0.5
    return k == int(k)

m = (1, 0, 0)
for D in range(2, 1001):
    if not is_square(D):
        t = dsolve(D) + (D,)
        if t[0] > m[0]:
            m = t

print('Solution:', m)
end = perf_counter()
print(end - start, 'seconds to run')
