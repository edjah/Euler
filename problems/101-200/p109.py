import time
start = time.time()

regions = list(range(1, 21)) + [25]
scores = [m * r for r in range(1, 21) for m in range(1, 4)] + [25, 50]

def checkout(score, idx=0, remaining=3):
    if remaining <= 0 or score <= 1:
        return 0

    tot = 0
    for r in regions:
        if 2 * r == score:
            tot += 1

    if remaining > 1:
        for i in range(idx, len(scores)):
            tot += checkout(score - scores[i], i, remaining - 1)

    return tot

sol = sum(checkout(score) for score in range(1, 100))
print("Solution:", sol)

end = time.time()
print(f"{end - start:.3f} sec")
