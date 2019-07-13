from lib.utility import start_time, end_time
start_time()


def S(n, r, acc):
    if acc[-n:] in acc[:-1]:
        return 0
    elif r == 0:
        t = acc + acc[:n - 1]
        for i in range(2 ** n):
            if t[i:i + n] in t[:i + n - 1]:
                return 0
        return int(acc, 2)

    return S(n, r - 1, acc + '0') + S(n, r - 1, acc + '1')


n = 5
sol = S(n, 2 ** n - n, '0' * n)
print('Solution:', sol)
end_time()
