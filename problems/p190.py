from time import perf_counter
start = perf_counter()

def P(m):
    prod = 1
    for i in range(1, m + 1):
        prod *= (2 * i / (m + 1)) ** i
    return int(prod)

solution = sum(P(m) for m in range(2, 16))
print('Solution:', solution)

end = perf_counter()
print(f"{end - start:f} seconds to run")
