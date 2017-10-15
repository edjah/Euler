import time
from tqdm import tqdm


def area(a, b, c):
    p = (a + b + c) / 2
    return (p * (p - a) * (p - b) * (p - c)) ** 0.5


def perfect(n):
    return n == int(n)


start = time.time()
tot = 0
lim = 10 ** 9
for s in tqdm(range(3, lim // 3 + 1, 2)):
    if perfect(area(s, s, s + 1)):
        tot += 3 * s + 1
    elif perfect(area(s, s, s - 1)):
        tot += 3 * s - 1

print('Solution:', tot)

end = time.time()
print('%f seconds to run' % (end - start))
