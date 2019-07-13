from lib.utility import start_time, end_time, subsets
start_time()


def solve(n):
    ans = 0
    s = set(range(n))
    for u in subsets(s):
        for v in subsets(s - set(u)):
            if len(u) != len(v):
                continue

            # Check if in a case like (A, D) vs (B, C) where its not obvious
            # which subset is bigger like it would be in the case of
            # (A, B) and (C, D)
            if any(x >= y for x, y in zip(*sorted([u, v]))):
                ans += 1

    return ans // 2


print('Solution:', solve(12))
end_time()
