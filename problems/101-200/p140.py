"""
Modified Fibonacci generating function is: (x + 3x^2) / (1 - x - x^2)
(x + 3x^2) / (1 - x - x^2) = n => x = (sqrt(5n^2 + 14n + 1) - n - 1) / (2n + 6)

We need to 5n^2 + 14n + 1 to equal some square number: y^2.
This is a Diophantine equation: 5n^2 + 14n + 1 - y^2 = 0
Solved via: http://www.alpertron.com.ar/QUAD.HTM
"""
from lib.utility import start_time, end_time
start_time()


def diophantine_solve(n, base_case):
    if n <= 0:
        return base_case

    xn_1, yn_1 = diophantine_solve(n - 1, base_case)
    xn = -9*xn_1 - 4*yn_1 - 14
    yn = -20*xn_1 - 9*yn_1 - 28
    return xn, yn


solutions = []
for base_case in [(2, -7), (0, -1), (0, 1), (-4, 5), (-3, 2), (-3, -2)]:
    for n in range(30):
        x, y = diophantine_solve(n, base_case)
        if x > 0:
            solutions.append(x)

solutions = sorted(set(solutions))[:30]
print('Solution:', sum(solutions))
end_time()
