from time import perf_counter
start = perf_counter()

def count(n):
    if n == 0:
        return 1


end = perf_counter()
print(end - start, 'seconds to run')
