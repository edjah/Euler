import time
import random
from math import log2
from lib.utility import memoize
start = time.time()

def get_children(state):
    children = []
    for paper in state:
        child = list(state[:])
        child.remove(paper)
        for _ in range(int(log2(paper))):
            paper //= 2
            child.append(paper)
        children.append(tuple(sorted(child)))

    return children

@memoize
def solve(i, prob, state):
    ans = prob * (len(state) == 1) * (i % 15 > 0)
    children = get_children(state)
    for c in children:
        ans += solve(i + 1, prob / len(children), c)

    return ans

ans = solve(0, 1, (16,))
print("Solution: {:.6f}".format(ans))


end = time.time()
print(f"{(end - start):.3f} sec")
