from time import perf_counter
start = perf_counter()

count = 0
def S(n, r, acc):
    global count
    if acc[-n:] in acc[:-1]:
        return 0
    elif r <= 0:
        t = acc + acc[:n - 1]
        for i in range(2 ** n):
            if t[i:i + n] in t[:i + n - 1]:
                return 0
        count += 1
        return int(acc, 2)
    return S(n, r-1, acc + '0') + S(n, r-1, acc + '1')

n = 5
sol = S(n, 2 ** n - n, '0' * n)
print('Solution:', sol)
print('Count:', count)

end = perf_counter()
print(end - start, 'seconds to run')
