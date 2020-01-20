from lib.utility import start_time, end_time
import numpy as np
start_time()


def get_probs(k, n):
    if k == 1:
        return {-2: 0, -1: 8/36, 0: 19/36, 1: 8/36, 2: 1/36}
    elif k < n // 2 - 1:
        return {-2: 1/36, -1: 8/36, 0: 18/36, 1: 8/36, 2: 1/36}
    elif k == n // 2 - 1:
        return {-2: 1/36, -1: 8/36, 0: 19/36, 1: 8/36, 2: 0}
    elif k == n // 2:
        return {-2: 2/36, -1: 16/36, 0: 18/36, 1: 0, 2: 0}

    assert False


def solve_linear_system(n):
    mat_limit = n // 2
    a = np.zeros((mat_limit, mat_limit))
    b = np.zeros(mat_limit)

    # building the linear system
    for k in range(mat_limit):
        b[k] = -1

        a[k][k] = -1
        for dk, prob in get_probs(k + 1, n).items():
            if k + dk >= 0 and k + dk < mat_limit:
                a[k][k + dk] += prob

    # solving ax = b for x
    x = np.linalg.solve(a, b)
    return x[-1]


ans = solve_linear_system(100)
print(f'Solution: {ans:.10g}')
end_time()
