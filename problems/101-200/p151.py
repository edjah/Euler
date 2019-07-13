from lib.utility import memoize, start_time, end_time
from math import log2
start_time()


def get_child_states(state):
    children = []
    for paper in state:
        child = list(state)
        child.remove(paper)
        for _ in range(int(log2(paper))):
            paper //= 2
            child.append(paper)
        children.append(tuple(sorted(child)))

    return children


@memoize
def solve(i, prob, state):
    ans = prob * (len(state) == 1) * (i != 0 and i != 15)
    children = get_child_states(state)
    for c in children:
        ans += solve(i + 1, prob / len(children), c)

    return ans


ans = solve(0, 1, (16,))
print("Solution: {:.6f}".format(ans))
end_time()
