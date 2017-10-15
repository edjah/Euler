from time import perf_counter
start = perf_counter()

def test(s, r):
    return (3*r - s) * (r + s)

s = 2400
for r in range(1, 15):
    print((s, r), test(s, r) - test(s, r - 1))

# lim = 10 ** 6
lim = 1200
a = {}

for s in range(1, lim // 3 + 1):
    n = test(s, s // 3 - 1)
    while n < lim:
        if n > 0:
            if n in a:
                a[n] += 1
            else:
                a[n] = 1
        n += 6
print(a)

b = {}
for i in a:
    if a[i] in b:
        b[a[i]] += 1
    else:
        b[a[i]] = 1

ans = b.get(10, 0)
print('Solution:', ans)


end = perf_counter()
print(end - start, 'seconds to run')
