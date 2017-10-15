from time import perf_counter
start = perf_counter()

d = {1}
lim = 10 ** 12
for b in range(2, int(lim ** 0.5) + 1):
    for n in range(3, 40):
        r = (b ** n - 1) // (b - 1)
        if r < lim:
            d.add(r)
        else:
            break

print('Solution:', sum(d))


end = perf_counter()
print(end - start, 'seconds to run')
