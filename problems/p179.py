from time import perf_counter
start = perf_counter()


def divisor_count_tbl(n):
    tbl = [1] * (n + 1)
    for i in range(1, n + 1):
        for j in range(i + i, n + 1, i):
            tbl[j] += 1
    return tbl

lim = 10 ** 7
a = divisor_count_tbl(lim)
tot = 0
for i in range(1, lim):
    if a[i] == a[i + 1]:
        tot += 1

print('Solution:', tot) # 986262

end = perf_counter()
print(end - start, 'seconds to run')
