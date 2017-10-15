from time import perf_counter
start = perf_counter()

def cubic_perms(n):
    storage = {}
    i = 0
    while True:
        x = i ** 3
        s = ''.join(sorted(str(x)))
        if s in storage:
            storage[s].append(x)
            if len(storage[s]) >= n:
                return min(storage[s])
        else:
            storage[s] = [x]
        i += 1

solution = cubic_perms(5)
print('Solution:', solution)


end = perf_counter()
print(end - start, 'seconds to run')
