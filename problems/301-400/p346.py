from time import perf_counter
start = perf_counter()

d = [1]
lim = 10 ** 12
for b in range(2, int(lim ** 0.5) + 1):
    for n in range(3, 40):
        r = (b ** n - 1) // (b - 1)
        if r < lim:
            d.append(r)
        else:
            break

print('Solution:', sum(set(d)))


end = perf_counter()
print("{:.4f} sec".format(end - start))
