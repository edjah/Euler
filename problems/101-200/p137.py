"""
Fibonacci generating function is: z / (1 - z - z^2)
z / (1 - z - z^2) = n  =>  z = (sqrt(5n^2 + 2n + 1) - n - 1) / 2n

We need to 5n^2 + 2n + 1 to equal some square number: y^2.
This is a Diophantine equation: 5x^2 + 2x + 1 - y^2 = 0
Solved via: http://www.alpertron.com.ar/QUAD.HTM
"""
from lib.utility import start_time, end_time
start_time()


def diophantine_solve(n, base_case):
    if n <= 0:
        return base_case

    xn_1, yn_1 = diophantine_solve(n - 1, base_case)
    xn = -9*xn_1 - 4*yn_1 - 2
    yn = -20*xn_1 - 9*yn_1 - 4
    return xn, yn


solutions = []
for base_case in [(0, 1), (2, 5), (0, -1), (-1, 2), (-1, -2)]:
    for n in range(15):
        x, y = diophantine_solve(n, base_case)
        if x > 0:
            solutions.append(x)

solutions = sorted(set(solutions))
print('Solution:', solutions[14])
end_time()
