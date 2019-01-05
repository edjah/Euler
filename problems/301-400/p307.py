from lib.utility import start_time, end_time
from math import factorial
from random import randint
start_time()

k = 4
n = 10
target = 3

trials = 10 ** 6
tot = 0
for _ in range(trials):
    a = [0] * n
    for i in range(k):
        a[randint(0, n - 1)] += 1
    tot += any(x >= target for x in a)
print("Observed: {:.10f}".format(tot / trials))


# p = 1
# for i in range(1, k - 1):
#     t = 0
#     for j in range(i):
#         t +=  (n - j) / n

p = ((n - 1)/n * (1 + 1/n)) * ((n-2)*(n-1)/n**2 * (n)/n + 3*(n-1)/n**2 * (n-1)/n)

print("Expected: {:.10f}".format(1-p))

# print(num / den)


end_time()
