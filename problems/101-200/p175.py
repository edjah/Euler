from lib.utility import start_time, end_time
from collections import deque
start_time()

goal = "13717421 / 109739369"


def log2(n):
    import math
    return int(math.log2(n))


def f(n):
    solutions = set()
    original_binary = [int(i) for i in bin(n)[2:]]
    queue = deque([original_binary])

    solutions.add(tuple(original_binary))

    while queue:
        binary = queue.popleft()
        for i in range(len(binary) - 1):
            if binary[i] >= 1 and binary[i + 1] == 0:
                copy = binary[:]
                copy[i] -= 1
                copy[i + 1] = 2
                if tuple(copy) not in solutions:
                    solutions.add(tuple(copy))
                    queue.append(copy)

    return len(solutions)


import matplotlib.pyplot as plt
import numpy as np
x = list(range(0, 15001))
y = [f(i) for i in x]
print(np.argmax(y))
plt.plot(x, y)
plt.plot(x, 10*np.sqrt(x))
plt.show()

# print(f(24100))
# print(f2(109739369))

for i in range(1000):
    assert(f(i) == f(i))



end_time()

# 174762
#
