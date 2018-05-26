import time
from lib.utility import memoize
from collections import deque
start = time.time()

def random_generator():
    k = 1
    s = deque([], 55)
    while True:
        if 1 <= k <= 55:
            nxt = 100003 - 200003 * k + 300007 * k ** 3
        else:
            nxt = s[31] + s[0] + 1000000
        nxt = (nxt % 1000000) - 500000
        s.append(nxt)
        k += 1
        yield nxt


def best_in_series(series):
    best = curr = 0
    for a in series:
        curr += a
        if curr > best:
            best = curr
        if curr < 0:
            curr = 0

    return best

def max_sum_subsequence(M):
    size = len(M)
    best = 0

    for i in range(size):
        # row best
        best = max(best, best_in_series(M[i]))

        # column best
        col = [M[j][i] for j in range(size)]
        best = max(best, best_in_series(col))

        # diagonal bests
        diags = [
            ((i, 0), (1, 1)),
            ((0, i), (1, 1)),
            ((i, 0), (-1, 1)),
            ((size - 1, i), (-1, 1)),
        ]
        for (a, b), (dx, dy) in diags:
            s = []
            while 0 <= a < size and 0 <= b < size:
                s.append(M[a][b])
                a += dx
                b += dy
            best = max(best, best_in_series(s))

    return best

rand = random_generator()
nums = [next(rand) for i in range(4 * 10 ** 6)]
mat = [nums[2000*i:2000*(i + 1)] for i in range(2000)]

a = max_sum_subsequence(mat)
print("Solution:", a)

end = time.time()
print(f"{end - start:.3f} sec")
