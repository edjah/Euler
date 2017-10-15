from math import sqrt
from time import clock
start = clock()

def num_rects(a, b):
    return a * (a + 1) * b * (b + 1) // 4

target = 2000000
k = float('inf')
best = 0
for i in range(1, 100):
    for j in range(1, 100):
        x = num_rects(i, j)
        if abs(x - target) < k:
            k = abs(x - target)
            best = (i, j)

x = num_rects(best[0], best[1])
print('Grid:', best)
print('Num rects:', x)
print('Error:', abs(x - target))
print('Solution:', best[0] * best[1])

end = clock()
print(1000 * (end - start), "milliseconds to run")
