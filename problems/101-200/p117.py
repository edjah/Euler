from time import perf_counter
start = perf_counter()

cache = {}
def ways(tiles, length):
    if length in cache:
        return cache[length]
    if length < 0:
        return 0
    elif length == 0:
        return 1
    tot = sum(ways(tiles, length - t) for t in tiles)
    cache[length] = tot
    return tot

ans = ways((1, 2, 3, 4), 50)
print('Solution:', ans)

end = perf_counter()
print(end - start, 'seconds to run')
