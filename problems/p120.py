from time import perf_counter
start = perf_counter()

def rmax(a):
    asq = a * a
    best = 0
    for n in range(2 * a):
        k = 2 * a * n if n % 2 == 1 else 2
        best = max(best, k % asq)
    return best

tot = 0
for i in range(3, 1001):
    tot += rmax(i)
print('Solution:', tot)


end = perf_counter()
print(end - start, 'seconds to run')
