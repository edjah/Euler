from time import perf_counter
start = perf_counter()

def random_generator():
    k = 1
    s = [0]
    while True:
        if 1 <= k <= 55:
            nxt = 100003 - 200003 * k + 300007 * k ** 3
        else:
            nxt = s[k - 24] + s[k - 55] + 1000000
        nxt = (nxt % 1000000) - 500000
        s.append(nxt)
        k += 1
        yield nxt


# rand = random_generator()
# nums = [next(rand) for i in range(4 * 10 ** 6)]
# mat = [nums[2000*i:2000*(i + 1)] for i in range(2000)]

M = [
        [-2, 5, 3, 2],
        [9, -6, 5, 1],
        [3, 2, 7, 3],
        [-1, 8, -4, 8]
    ]


def max_sum_subsequence(M):
    cache = {}
    size = len(M)
    def D(i, j, dir):
        if (i, j, dir) in cache:
            return cache[(i, j, dir)]
        if i == size - 1 or j == size - 1:
            return D[i][j]
        if dir == 1:
            pass
        elif dir == 2:
            pass
        elif dir == 3:
            pass
        elif dir == 4:
            pass

        cache[(i, j, dir)] = best
        return best


a = max_sum_subsequence(M)
print(a)

end = perf_counter()
print(end - start, 'seconds to run')
