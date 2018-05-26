from time import perf_counter
start = perf_counter()

def bouncy(n):
    a = [int(i) for i in str(n)]
    up = down = False
    for i in range(len(a) - 1):
        up = up or  a[i] < a[i + 1]
        down = down or  a[i] > a[i + 1]
    return up and down

bounce = 0
tot = 1
while bounce/tot < 0.99:
    bounce += bouncy(tot)
    tot += 1

print(tot)

end = perf_counter()
print(end - start, 'seconds to run')
