from time import perf_counter
from itertools import combinations
start = perf_counter()


def M(N):
    optimals = {1: 0}
    curr, nxt = [(1,)], []
    step = 0
    while not all(i in optimals for i in range(2, N + 1)):
        step += 1
        tmp_opts = {}
        for tup in curr:
            for i in range(len(tup)):
                for j in range(i, len(tup)):
                    x = tup[i] + tup[j]
                    if x not in optimals:
                        tmp_opts[x] = step
                        nxt.append(tup + (x,))

        optimals.update(tmp_opts)
        curr, nxt = nxt, []

    return sum(optimals[i] for i in range(2, N + 1))

sol = M(200)
print('Solution:', sol)

end = perf_counter()
print(end - start, 'seconds to run')
