from time import perf_counter
import sys

start = perf_counter()

def S(a, b, c):
    cache = {}
    def F(n):
        if n in cache:
            return cache[n]
        if n > b:
            return n - c
        ans = F(a + F(a + F(a + F(a + n))))
        cache[n] = ans
        return ans

    tbl = [F(n) for n in range(b + 1)]
    print(tbl[0], tbl[1])
    print(tbl[500])
    # for i in range(lesn(tbl)):
    #     # if tbl[i] != tbl[i - 1] + 1:
    #         # print('Diff: %d vs %d\n' % (tbl[i - 1] - tbl[i], 4*a - 3*c - 1))
        # print('%d: %d' % (i, tbl[i]))
    return sum(tbl)

def sum_range(a, b):
    return (b + a) * (b - a + 1) // 2

def S2(a, b, c):
    start = (4 * (a - c) + c) * (b // a + 1) - c
    range_sums = [start]
    k = 0
    for i in range(1, b + 1, a):
        k += 1
        v = start - (4*a - 3*c - 1) * k + i + c//2
        w = v + min(a - 1, a - 1)
        print(i, v, w)
        range_sums.append(sum_range(v, w))
    print(range_sums)
    return sum(range_sums)

a, b, c = 60, 2000, 40
x = S(a, b, c)
y = S2(a, b, c)
print(x, 'vs', y)


end = perf_counter()
print(end - start, 'seconds to run')
