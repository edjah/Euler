from time import perf_counter
start = perf_counter()

cache = {}
def calc(a, l, k):
    if l > 1 or a > 2:
        return 0
    elif k <= 0:
        return 1
    elif (a, l, k) in cache:
        return cache[(a, l, k)]
    t = 0
    t += calc(0, l, k - 1)
    t += calc(a + 1, l, k - 1)
    t += calc(0, l + 1, k - 1)
    cache[(a, l, k)] = t
    return t

solution = calc(0, 0, 30)
print('Solution:', solution)

end = perf_counter()
print(end - start, 'seconds to run')
