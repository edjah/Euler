from lib.utility import start_time, end_time, nCr
start_time()


def p(n):
    return nCr(26, n) * (2**n - n - 1)


print('Solution:', max(p(n) for n in range(27)))
end_time()
