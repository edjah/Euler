from time import perf_counter
start = perf_counter()

cache = {}
def W(prev, acc, max_r, r, c):
    tup = (prev, acc, r, c)
    if tup in cache:
        return cache[tup]
    if r == 0 and c == 1:
        return 1
    tot = 0
    if r == 0 and c > 1:
        return W(acc, (), max_r, max_r, c - 1)
    else:
        for d in [2, 3]:
            n = r - d
            if n == 0 or (n > 0 and n not in prev):
                tot += W(prev, acc + (n,), max_r, n, c)

    cache[tup] = tot
    return tot

a = W((), (), 32, 32, 10)
print(a)



end = perf_counter()
print(end - start, 'seconds to run')
