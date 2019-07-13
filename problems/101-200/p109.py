from lib.utility import start_time, end_time
start_time()

scores = [m * r for r in range(1, 21) for m in range(1, 4)] + [25, 50]


def checkout(score, idx=0, remaining=3):
    if remaining <= 0 or score <= 1:
        return 0

    tot = 0
    if score < 50 and score % 2 == 0:
        tot += 1

    if remaining > 1:
        for i in range(idx, len(scores)):
            tot += checkout(score - scores[i], i, remaining - 1)

    return tot


sol = sum(checkout(score) for score in range(1, 100))
print('Solution:', sol)
end_time()
