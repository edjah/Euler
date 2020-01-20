from lib.utility import start_time, end_time, memoize
start_time()


def P(k, q):
    probs = [1 - x/q for x in range(1, 51)]

    @memoize
    def rec(num_shots, score):
        if num_shots == 50:
            return score == k

        p = rec(num_shots + 1, score + 1) * probs[num_shots]
        p += rec(num_shots + 1, score) * (1 - probs[num_shots])
        return p

    return rec(0, 0)


lo = 50
hi = 100
while hi - lo > 1e-10:
    mid = (lo + hi) / 2
    if P(20, mid) < 0.02:
        hi = mid
    else:
        lo = mid

print(f'Solution: {lo:.10f}')

end_time()
