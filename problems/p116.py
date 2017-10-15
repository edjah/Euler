from time import perf_counter
start = perf_counter()

cache = {}
def ways(m, length, used):
    if (m, length, used) in cache:
        return cache[(m, length, used)]
    if length < 0:
        return 0
    elif length == 0 and used:
        return 1
    tot = ways(m, length - 1, used)
    tot += ways(m, length - m, True)
    cache[(m, length, used)] = tot
    return tot

ans = ways(2, 50, 0) + ways(3, 50, 0) + ways(4, 50, 0)
print('Solution:', ans)

end = perf_counter()
print(end - start, 'seconds to run')
