import time
from itertools import combinations

__tstamp_start = None


def humanize_duration(duration):
    if duration < 1:
        return f'{1e3 * duration:.3f} ms'
    elif duration < 60:
        return f'{duration:.3f} sec'
    else:
        return f'{duration // 60:.0f} min {duration % 60:.0f} sec'


def start_time():
    global __tstamp_start
    __tstamp_start = time.time()


def end_time():
    if __tstamp_start is None:
        print('start_time() was never called')
        return

    print(humanize_duration(time.time() - __tstamp_start))


def time_function(f):
    def func(*args, **kwargs):
        start = time.time()
        result = f(*args, **kwargs)
        end = time.time()

        args_str = ', '.join(map(repr, args))
        kwargs_str = ', '.join(f'{k}={repr(v)}' for k, v in kwargs.items())
        if args_str and kwargs_str:
            args_str += ', '

        duration = humanize_duration(end - start)
        print(f'{f.__name__}({args_str}{kwargs_str}): {duration}')

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
