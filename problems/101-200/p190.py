from lib.utility import start_time, end_time


def P(m):
    prod = 1
    for i in range(1, m + 1):
        prod *= (2 * i / (m + 1)) ** i
    return int(prod)


start_time()
solution = sum(P(m) for m in range(2, 16))
print('Solution:', solution)
end_time()
