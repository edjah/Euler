from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def count_ways(length, is_red=False):
    if length < 0:
        return 0
    elif length == 0:
        return 1

    tot = count_ways(length - 1, False)
    if not is_red:
        for i in range(3, length + 1):
            tot += count_ways(length - i, True)
    return tot


print('Solution:', count_ways(50, False))
end_time()
