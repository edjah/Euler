"""
b must be even. two cases. h = b + 1 and h = b - 1
h^2 = (b + 1)^2 = L^2 - (b / 2)^2    =>    5b^2 + 8b - 4L^2 + 4 = 0
h^2 = (b - 1)^2 = L^2 - (b / 2)^2    =>    5b^2 - 8b - 4L^2 + 4 = 0

These are two Diophantine equations, but they happen to have identical solutions
Solved via: http://www.alpertron.com.ar/QUAD.HTM
"""
from lib.utility import start_time, end_time
start_time()


def diophantine_solve(n):
    if n <= 0:
        return (0, 1)

    xn_1, yn_1 = diophantine_solve(n - 1)
    xn = -9*xn_1 - 8*yn_1 - 8
    yn = -10*xn_1 - 9*yn_1 - 8
    return xn, yn


ans = 0
for n in range(1, 13):
    x, y = diophantine_solve(n)
    ans += abs(y)

print('Solution:', ans)
end_time()
