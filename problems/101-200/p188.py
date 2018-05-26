from time import perf_counter
start = perf_counter()

a = curr = 1777
mod = 10 ** 8
for i in range(1885):
    curr = pow(a, curr, mod)
print('Solution:', curr)

end = perf_counter()
print(end - start, 'seconds to run')
