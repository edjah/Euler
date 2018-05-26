from time import perf_counter
start = perf_counter()

def works(n):
    return all(i in '012' for i in str(n))

def f(n):
    a = n
    while not works(a):
        a += n
    return a


print(f(198))


end = perf_counter()
print(end - start, 'seconds to run')
