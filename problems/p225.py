from time import perf_counter
start = perf_counter()

cache = {}
def T(n):
    if n in cache:
        return cache[n]
    if n <= 3:
        return 1
    ans = T(n - 1) + T(n - 2) + T(n - 3)
    cache[n] = ans
    return ans

for i in range(1, 2700):
    # print(T(i) / T(i - 1))
    T(i)/T(i - 1)


end = perf_counter()
print(end - start, 'seconds to run')
