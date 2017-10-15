from time import perf_counter
start = perf_counter()

def is_power_of_two(n):
    return n != 0 and n & (n - 1) == 0;

c, x = 1, 3
while c/x >= 1/12345:
    if is_power_of_two(x):
        c += 1
    x += 1

x += 1
print('Solution:', x * (x - 1))

end = perf_counter()
print(end - start, 'seconds to run')
