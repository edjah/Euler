from time import perf_counter
start = perf_counter()

def streak(n):
    k = 0
    while n % (k + 1) == 0:
        n += 1
        k += 1
    return k

a = streak(120)

def P(s, N):
    # c = sum(streak(n) == s for n in range(2, N))
    c = 0
    l = 0
    for n in range(2, N):
        q = streak(n)
        if q == s:
            print(n, s, '(%d)' % (n - l))
            c += 1
            l = n
    return c

a = P(15, 10 ** 7)
print(a)


end = perf_counter()
print(end - start, 'seconds to run')
