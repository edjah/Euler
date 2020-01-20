from lib.utility import start_time, end_time
from decimal import getcontext, Decimal
start_time()


getcontext().prec = 100


# uses this idea: https://en.wikipedia.org/wiki/Mediant_(mathematics)
def best_sqrt_approx(x, denominator_bound):
    whole_part = int(Decimal(x).sqrt())
    fractional_part = Decimal(x).sqrt() - whole_part

    lo = (0, 1)
    hi = (1, 1)

    while True:
        mid = (lo[0] + hi[0], lo[1] + hi[1])
        if mid[1] > denominator_bound:
            break

        decimal = Decimal(mid[0]) / Decimal(mid[1])
        if decimal > fractional_part:
            hi = mid
        elif decimal < fractional_part:
            lo = mid

    lo_error = abs(Decimal(lo[0]) / Decimal(lo[1]) - fractional_part)
    hi_error = abs(Decimal(hi[0]) / Decimal(hi[1]) - fractional_part)
    r = lo if lo_error < hi_error else hi
    return (r[0] + r[1] * whole_part, r[1])


denominator_bound = 10 ** 12
solution = 0

for n in range(1, 100001):
    if round(n ** 0.5) ** 2 != n:
        solution += best_sqrt_approx(n, denominator_bound)[1]

print('Solution:', solution)
end_time()
