from time import perf_counter
start = perf_counter()

def triple_lengths(m, n, lim):
    t = 2*m*m + 2*m*n
    o = tuple(sorted((m*m - n*n, 2*m*n, m*m + n*n)))
    x = []
    k = 1
    while t * k <= lim:
        x.append((k * o[0], k * o[1], k * o[2]))
        k += 1
    return x

lim = 1500000

s = set()
for m in range(2, int(lim ** 0.5)):
    for n in range(1, m):
        if 2*m*m + 2*m*n > lim:
            break
        for z in triple_lengths(m, n, lim):
            s.add(z)

lens = [a[0] + a[1] + a[2] for a in s]
d = {}
for i in lens:
    if i in d:
        d[i] += 1
    else:
        d[i] = 1

valid = list(filter(lambda x: d[x] == 1, d))
print('Solution:', len(valid))


end = perf_counter()
print(end - start, 'seconds to run')
