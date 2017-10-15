from time import clock
from decimal import *
start = clock()

getcontext().prec = 200
def sqrt_digital_sum(n):
    s = str(Decimal(n).sqrt())
    if '.' not in s:
        return 0
    s = s.replace('.', '')
    return sum(map(int, s[:100]))

t = 0
for i in range(101):
    t += sqrt_digital_sum(i)

print('Solution:', t)

end = clock()
print(end - start, 'seconds to run')
