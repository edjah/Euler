from lib.utility import start_time, end_time
import numpy as np
start_time()


def generating_function(n):
    return 1 - n ** 1 + n ** 2 - n ** 3 + n ** 4 - n ** 5 \
             + n ** 6 - n ** 7 + n ** 8 - n ** 9 + n ** 10


def compute_FIT(y):
    degree = len(y) - 1
    x = np.arange(len(y)) + 1
    poly = np.poly1d(np.polyfit(x, y, degree))
    return poly(degree + 2)


total = 0
y = np.array([generating_function(i) for i in range(1, 11)])
for degree in range(0, 10):
    total += compute_FIT(y[:degree + 1])

print('Solution:', int(round(total)))
end_time()
