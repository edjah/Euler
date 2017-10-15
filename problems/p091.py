from multiprocessing import Pool
from time import perf_counter
start = perf_counter()

def is_right(x1, y1, x2, y2):
    l1 = x1 ** 2 + y1 ** 2
    l2 = x2 ** 2 + y2 ** 2
    l3 = (x1 - x2) ** 2 + (y1 - y2) ** 2
    k = sorted([l1, l2, l3])
    return all(k) and k[0] + k[1] == k[2]

N = 50
def test(x1):
    ans = 0
    for y1 in range(0, N + 1):
        for x2 in range(x1, N + 1):
            for y2 in range(0, y1 + 1):
                if is_right(x1, y1, x2, y2):
                    ans += 1
    return ans

sol = 0
pool = Pool(4)
for ans in pool.imap_unordered(test, range(N + 1)):
    sol += ans

print('Solution:', sol)

end = perf_counter()
print(end - start, 'seconds to run')
