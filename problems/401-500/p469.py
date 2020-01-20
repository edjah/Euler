from lib.utility import start_time, end_time
start_time()


def trial(n):
    import random

    x = [1] * n
    x = [1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0]
    available = set(i for i in range(len(x)) if x[i])
    n = len(x)

    while available:
        chair = random.choice(list(available))
        x[chair] = 0
        available.remove(chair)
        available.discard((chair + 1) % n)
        available.discard((chair - 1) % n)

    return sum(x)


for n in range(2, 16):
    r = [trial(n) for i in range(10000)]
    print(n, '|', sum(r) / len(r))


end_time()

"""
2 + 1 + 1 1
0 0  ---  0 0 0
- -  ---  0 0 -
000---000---000

"""
