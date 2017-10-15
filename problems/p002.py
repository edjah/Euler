from time import perf_counter
start = perf_counter()

tot = 0
a = b = 1
while b < 4000000:
    if b % 2 == 0:
        tot += b
    a, b = b, a + b

print('Solution:', tot)

end = perf_counter()
print(end - start, 'seconds to run')
