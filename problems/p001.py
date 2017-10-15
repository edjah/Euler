from time import perf_counter
start = perf_counter()

tot = 0
for i in range(1, 1000):
    if i % 3 == 0 or i % 5 == 0:
        tot += i

print('Solution:', tot)

end = perf_counter()
print(end - start, 'seconds to run')
