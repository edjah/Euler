from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def f(n):
    if n == 0:
        return 1

    if n % 2 == 0:
        return f(n // 2) + f((n - 2) // 2)
    else:
        return f((n - 1) // 2)


limit = 10 ** 25
print('Solution:', f(limit))
end_time()
