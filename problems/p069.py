import prime
from time import clock

start = clock()

prime.init(10 ** 6)

best_n, best_ratio = 0, 0
for n in range(2, 10**6 + 1):
    r = n/prime.totient(n)
    if r > best_ratio:
        best_ratio = r
        best_n = n

print('Solution:', best_n)
print('Totient:', prime.totient(best_n))
print('Ratio:', best_ratio)

end = clock()
print('Time to run:', end - start, 'seconds')
