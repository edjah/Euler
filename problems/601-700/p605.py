import time
import random
from collections import deque
start = time.time()

def fair_flip():
    return random.random() < 0.5

def trial(n):
    r = 1
    prev_res = None
    while True:
        res = fair_flip()
        if res == True and prev_res == False:
            return ((r - 1) % n) + 1

        prev_res = res
        r += 1


def simulate(n, k, trials=10000):
    ntrials = 10 ** 4
    s = sum([trial(n) == k for _ in range(trials)])
    return s / trials

def exact(n, k):
    pass


"""
Pn(k) = P

"""


print('Simulation:', simulate(2, 2, 10000))
print('Expected:', 12 / 49)

end = time.time()
print(f"{1000 * (end - start):.3f} ms")
