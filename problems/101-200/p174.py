from lib.utility import start_time, end_time
start_time()


def count(k):
    return 4 * (k + 1)


lim = 10 ** 6
a = {}
t = 0
for i in range(1, lim // 4 + 1):
    k = count(i)
    c = 0
    while k <= lim:
        if k in a:
            a[k] += 1
        else:
            a[k] = 1
        c += 1
        i += 2
        k += count(i)
    t += c

b = {}
for i in a:
    if a[i] in b:
        b[a[i]] += 1
    else:
        b[a[i]] = 1

ans = sum(b[i] for i in range(1, 11))
print('Solution:', ans)
end_time()
