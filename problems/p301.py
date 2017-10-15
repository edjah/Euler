from time import perf_counter
start = perf_counter()

for i in range(2**30):
    pass

end = perf_counter()
print(end - start, 'seconds to run')
