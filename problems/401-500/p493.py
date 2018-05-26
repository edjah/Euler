import time
from lib.utility import memoize, nCr

# DP solution
start = time.time()

@memoize
def dfs(idx, counts, prob):
    if idx == 20:
        return prob * sum(int(c != 10) for c in counts)

    ans = 0
    for i in range(len(counts)):
        if counts[i] > 0:
            cpy = list(counts)
            cpy[i] -= 1
            p = prob * counts[i] / (70 - idx)
            ans += dfs(idx + 1, tuple(sorted(cpy)), p)

    return ans

ans = dfs(0, (10,) * 7, 1)

print("DP Solution: {:.9f}".format(ans))
end = time.time()
print(f"{1000 * (end - start):.3f} ms")



# stat 110 solution
start = time.time()

def stat110():
    prob = 1 - nCr(60, 20) / nCr(70, 20)
    return 7 * prob

ans = stat110()

print("\nStat 110 Solution: {:.9f}".format(ans))
end = time.time()
print(f"{1000 * (end - start):.3f} ms")
