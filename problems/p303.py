from time import perf_counter
start = perf_counter()

def works(n):
    return all(i in '012' for i in str(n))

def f(n):
    a = n
    m = 1
    while not works(a):
        a += n
    return a

tot = 0
for n in range(1, 101):
    tot += f(n)//n
    print(n, f(n)//n)

print('Solution:', tot)


end = perf_counter()
print(end - start, 'seconds to run')
