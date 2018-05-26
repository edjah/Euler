from time import perf_counter
start = perf_counter()

cache = {}
def count(uses, start, n):
    tup = (tuple(uses), start, n)
    if tup in cache:
        return cache[tup]
    if n <= 0:
        return int(all(uses))

    tot = 0
    for i in range(start, 16):
        if i < len(uses):
            u = uses[:]
            u[i] = True
            tot += count(u, 0, n - 1)
        else:
            tot += count(uses, 0, n - 1)
    cache[tup] = tot
    return tot

def inclusion_exclusion(n):
    A = 15 ** n
    B = 14 * 15 ** (n - 1)
    C = 14 * 15 ** (n - 1)

    AB = 14 ** n
    AC = 14 ** n
    BC = 13 * 14 ** (n - 1)

    ABC = 13 ** n

    bad = A + B + C - AB - AC - BC + ABC
    return 15 * 16**(n-1) - bad


# t = sum(count([False] * 3, 1, n) for n in range(1, 17))
# print('Solution:', hex(t)[2:].upper())

t = sum(inclusion_exclusion(n) for n in range(1, 17))
print('Solution:', hex(t)[2:].upper())

end = perf_counter()
print(end - start, 'seconds to run')
