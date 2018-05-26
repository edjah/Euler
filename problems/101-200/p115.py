from time import perf_counter
start = perf_counter()

cache = {}
def ways(m, length, red):
    if (m, length, red) in cache:
        return cache[(m, length, red)]
    if length < 0:
        return 1
    elif length == 0:
        return 1
    tot = ways(m, length - 1, False)
    if not red:
        for i in range(m, length + 1):
            tot += ways(m, length - i, True)
    cache[(m, length, red)] = tot
    return tot

ans = 0
while ways(50, ans, False) < 10 ** 6:
    ans += 1
print('Solution:', ans)
print('Ways:', ways(50, ans, False))

end = perf_counter()
print(end - start, 'seconds to run')
