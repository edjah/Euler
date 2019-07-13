from lib.utility import start_time, end_time
start_time()


def rmax(a):
    asq = a * a
    best = 0
    for n in range(2 * a):
        k = pow(a - 1, n, asq) + pow(a + 1, n, asq)
        best = max(best, k % asq)
    return best


tot = 0
for i in range(3, 1001):
    tot += rmax(i)

print('Solution:', tot)
end_time()
