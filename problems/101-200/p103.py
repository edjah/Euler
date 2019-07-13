from lib.utility import start_time, end_time, subsets
start_time()


def check_special_sum_set(s):
    if len(set(s)) != len(s):
        return False

    s = set(s)
    for x in subsets(s):
        for y in subsets(s - set(x)):
            if len(x) == len(y) == 0:
                continue
            a, b = sum(x), sum(y)
            if len(x) < len(y) and a >= b:
                return False
            if len(y) < len(x) and b >= a:
                return False
            if a == b:
                return False
    return True


def optimum(prev, n):
    # start off with the heuristic
    b = prev[len(prev) // 2]
    best = (b,) + tuple(a + b for a in prev)
    assert check_special_sum_set(best)

    seen = set()

    # fine tune the heuristic solution by searching nearby solutions
    def optimize(s, idx):
        nonlocal best

        if (s, idx) in seen:
            return

        if idx >= n:
            if check_special_sum_set(s) and sum(s) < sum(best):
                best = s
            return

        seen.add((s, idx))
        for i in range(-2, 2):
            a = list(s)
            a[idx] += i
            if check_special_sum_set(a[:idx + 1]):
                optimize(tuple(sorted(a)), idx + 1)

    print('Original sum:', sum(best))
    optimize(best, 0)
    print('Optimized sum:', sum(best))
    return sorted(best)


a = optimum([11, 18, 19, 20, 22, 25], 7)
print('Solution:', ''.join(str(i) for i in a))
end_time()
