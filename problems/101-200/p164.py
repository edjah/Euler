from time import perf_counter
start = perf_counter()

cache = {}
def count(s, n):
    if n <= 1:
        return 1
    tup = (s[-2:], n)
    if tup in cache:
        return cache[tup]

    tot = 0
    prev_sum = sum(int(i) for i in s[-2:])
    for digit in range(10 - prev_sum):
        tot += count(s + str(digit), n - 1)

    cache[tup] = tot
    return tot

d = 20
ans = sum(count(str(i), d) for i in range(1, 10))
print('Solution:', ans)

end = perf_counter()
print(end - start, 'seconds to run')
