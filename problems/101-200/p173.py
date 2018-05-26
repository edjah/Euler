from time import perf_counter
start = perf_counter()


def count(k):
    return 4 * (k + 1)


lim = 10 ** 6
t = 0
for i in range(1, lim // 4 + 1):
    k = count(i)
    c = 0
    while k <= lim:
        c += 1
        i += 2
        k += count(i)
    t += c

print('Solution:', t)



end = perf_counter()
print(end - start, 'seconds to run')
