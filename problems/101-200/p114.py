from time import perf_counter
start = perf_counter()

cache = {}
def ways(length, red):
    if (length, red) in cache:
        return cache[(length, red)]
    if length < 0:
        return 1
    elif length == 0:
        return 1
    tot = ways(length - 1, False)
    if not red:
        for i in range(3, length + 1):
            tot += ways(length - i, True)
    cache[(length, red)] = tot
    return tot

ans = ways(50, False)
print('Solution:', ans)

end = perf_counter()
print(end - start, 'seconds to run')
