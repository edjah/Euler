from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def ways(length):
    if length < 0:
        return 0
    elif length == 0:
        return 1

    tot = sum(ways(length - t) for t in range(1, 5))
    return tot


ans = ways(50)
print('Solution:', ans)
end_time()
