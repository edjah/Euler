from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def count(d0, d1, n):
    if n <= 1:
        return 1

    tot = 0
    for digit in range(10 - d0 - d1):
        tot += count(d1, digit, n - 1)

    return tot


d = 20
ans = sum(count(0, i, d) for i in range(1, 10))
print('Solution:', ans)
end_time()
