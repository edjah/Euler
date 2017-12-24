import time
from itertools import combinations

def time_function(f):
    def func(*args, **kwargs):
        start = 1000 * time.time()
        result = f(*args, **kwargs)
        end = 1000 * time.time()

        args_str = ", ".join(map(str, args))
        kwargs_str = ", ".join("{}={}".format(k, v) for k, v in kwargs.items())
        if args_str and kwargs_str:
            kwargs_str = ", " + kwargs_str
        print(f"{f.__name__}({args_str}{kwargs_str}): {end - start:.3f} ms")

        return result

    return func


def subsets(a, nonempty=True):
    for i in range(int(nonempty), len(a) + 1):
        for tup in combinations(a, i):
            yield tup

def nCr(n, k):
    ans = 1
    for i in range(min(k, n - k)):
        ans = (ans * (n - i)) // (i + 1)
    return ans

def nCr_tbl(n):
    tbl = [1] + [0] * n
    for i in range(n):
        tbl[i + 1] = (tbl[i] * (n - i)) // (i + 1)
    return tbl

def memoize(f):
    cache = {}
    def func(*args, **kwargs):
        if args not in cache:
            cache[args] = f(*args, **kwargs)
        return cache[args]

    return func

def find_missing(start, end):
    import os
    import re

    regex = re.compile(r'.*(\d{3})\.(py|c|cpp|java).*')
    present = set()
    for filename in os.listdir('.'):
        match = regex.match(filename)
        if match:
            present.add(int(match.group(1)))

    should_have = set(range(start, end + 1))

    return sorted(should_have - present)

if __name__ == '__main__':
    print(find_missing(1, 100))
