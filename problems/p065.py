from fractions import Fraction
from time import clock

start = clock()

tbl = [2] + sum([[1, 2*k, 1] for k in range(1, 100)], [])

def e(n, m):
    if n >= m - 1:
        return tbl[n]
    return tbl[n] + Fraction(1, e(n + 1, m))


approx = e(0, 100)
solution = sum(map(int, str(approx.numerator)))
print(solution)

end = clock()
print(end - start, 'seconds to run')
