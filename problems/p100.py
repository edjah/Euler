"""

 b(b-1)     1
------- =  ---
 n(n-1)     2

2b(b-1) = n(n-1)

2b^2 - 2b - n(n-1) = 0

     2 ± √(4 + 8n(n-1))      1 + √(2n^2 - 2n + 1)
b = -------------------- =  ----------------------
             4                        2
"""

from time import clock
from decimal import Decimal, getcontext
start = clock()


n = 1070379100000
getcontext().prec = 50
def B(n):
    ans = (1 + Decimal(2*n*n - 2*n + 1).sqrt()) / 2
    return ans

while True:
    b = B(n)
    if abs(b - round(b)) < 1e-20:
        print('B = %d; R = %d; N = %d' % (b, n - b, n))
        break
    n += 1

assert(2 * b * (b - 1) == n * (n - 1)), 'Solution is actually invalid'

end = clock()
print(end - start, 'seconds to run')

