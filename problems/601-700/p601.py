from math import ceil
from time import perf_counter
start = perf_counter()

def streak(n):
    k = 1
    while n % k == 0:
        n += 1
        k += 1
    return k - 1

def P(s, N):
    # c = sum(streak(n) == s for n in range(2, N))
    c = 0
    last = 0
    print(f"s = {s}\n-------")
    for n in range(2, N):
        if streak(n) == s:
            c += 1
            print(f"{c}: num: {n}, diff: {n - last}")
            last = n
    return c


def Pp(s, N):
    first = second = None
    for n in range(2, N):
        if streak(n) == s:
            if first is None:
                first = n
            elif second is None:
                second = n
                break

    if first and second:
        diff = second - first
        return ceil((N - first) / diff)
    else:
        return int(bool(first))



s, N = 12, 900000
a = P(s, N)
b = Pp(s, N)
print(f"actual: {a} vs expected: {b}")


end = perf_counter()
print(f"{end - start:.4f} seconds to run")
