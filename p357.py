from primes import miller_rabin
from time import clock

start_time = clock()

def test(n):
    l = n % 10
    if n > 6 and (l == 4 or l == 6):
        return False
    q = int(n ** 0.5) + 2
    for d in range(1, q):
        if n % d == 0:
            if not miller_rabin(d + n // d):
                return False
    return True

tot = 0
count = 0
l = 0
for i in range(0, 10**6, 2):
    if test(i):
        tot += i
        count += 1
        l = i

print('Total:', tot)
print('Count:', count)
end_time = clock()
print(end_time - start_time, "seconds")
