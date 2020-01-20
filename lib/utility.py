import time
import itertools
from collections import Counter

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

        # args_str = ', '.join(map(repr, args))
        # kwargs_str = ', '.join(f'{k}={repr(v)}' for k, v in kwargs.items())
        # if args_str and kwargs_str:
        #     args_str += ', '
        args_str = kwargs_str = ''

        duration = humanize_duration(end - start)
        print(f'{f.__name__}({args_str}{kwargs_str}): {duration}')

        return result

    return func


def subsets(a, nonempty=True):
    for i in range(int(nonempty), len(a) + 1):
        for tup in itertools.combinations(a, i):
            yield tup


def multi_subsets(multiset):
    items = []
    for item, count in sorted(Counter(multiset).items()):
        items.append([(item,) * c for c in range(count + 1)])

    for combo in itertools.product(*items):
        result = sum(combo, ())
        if len(result) > 0:
            yield result


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


def product(a):
    res = 1
    for x in a:
        res *= x
    return res


def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a


def lcm(a, b):
    return (a * b) // gcd(a, b)


def multi_gcd(*nums):
    if len(nums) == 0:
        return None

    result = nums[0]
    for n in nums[1:]:
        result = gcd(result, n)
    return result


def egcd(a, b):
    """
    returns (d, x, y) such that x*a + y*b == d
    """
    if b == 0:
        return (a, 1, 0)
    else:
        d, x, y = egcd(b, a % b)
        return (d, y, x - (a // b) * y)


def is_square(n):
    s = int(n ** 0.5)
    return s*s == n


def mod_inverse(r, modulus):
    gcd, x, y = egcd(r, modulus)
    assert gcd == 1, f'{r} does not have an inverse modulo {modulus}'
    return x % modulus


def memoize(f):
    def func(*args, **kwargs):
        if args not in func.cache:
            func.cache[args] = f(*args, **kwargs)
        return func.cache[args]

    func.cache = {}
    return func


def chunks(it, n):
    if isinstance(it, (list, tuple, str)):
        for i in range(0, len(it), n):
            yield it[i:i+n]
    else:
        chunk = []
        for x in it:
            chunk.append(x)
            if len(chunk) == n:
                yield chunk
                chunk = []

        if chunk:
            yield chunk


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
