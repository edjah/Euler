from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def ways(m, length, used):
    if length < 0:
        return 0
    elif length == 0:
        return 1 if used else 0

    tot = ways(m, length - 1, used) + ways(m, length - m, True)
    return tot


ans = ways(2, 50, False) + ways(3, 50, False) + ways(4, 50, False)
print('Solution:', ans)
end_time()
