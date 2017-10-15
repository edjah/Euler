from time import perf_counter
from fractions import Fraction
start = perf_counter()

cache = {}
def F(num, den, result, turn, limit):
    tup = (num, den, result)
    if tup in cache:
        return cache[tup]

    if turn > limit:
        if result > limit // 2:
            return Fraction(num, den)
        return 0

    tot = F(num * turn, den * (turn + 1), result, turn + 1, limit)
    tot += F(num, den * (turn + 1), result + 1, turn + 1, limit)
    cache[tup] = tot
    return tot

prob = F(1, 1, 0, 1, 15)
print('Prob:', prob, '~=', round(prob * 1.0, 8))
print('Max prize:', 1 // prob)


end = perf_counter()
print(end - start, 'seconds to run')
