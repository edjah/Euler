from time import perf_counter
x = list(range(10 ** 6))
trials = 10 ** 3

start = perf_counter()
for trial in range(trials):
    y = list(x)
end = perf_counter()
print('list(x): %f seconds to run' % (end - start))

start = perf_counter()
for trial in range(trials):
    y = x[:]
end = perf_counter()
print('x[:]: %f seconds to run' % (end - start))

start = perf_counter()
for trial in range(trials):
    y = []
    y.extend(x)
end = perf_counter()
print('y=[];y.extend(x): %f seconds to run' % (end - start))

start = perf_counter()
for trial in range(trials):
    y = [] + x
end = perf_counter()
print('[] + x: %f seconds to run' % (end - start))


start = perf_counter()
for trial in range(trials):
    y = x.copy()
end = perf_counter()
print('x.copy(): %f seconds to run' % (end - start))
