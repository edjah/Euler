from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def count_ways(m, length, is_red=False):
    if length < 0:
        return 0
    elif length == 0:
        return 1

    tot = count_ways(m, length - 1, False)
    if not is_red:
        for i in range(m, length + 1):
            tot += count_ways(m, length - i, True)
    return tot


ans = 0
while count_ways(50, ans, False) < 10 ** 6:
    ans += 1

print('Solution:', ans)
end_time()
