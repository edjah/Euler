"""
x + y = a^2  and  x - y = b^2     =>     2x = a^2 + b^2  and  2y = a^2 - b^2
y + z = e^2  and  y - z = f^2     =>     2z = e^2 - f^2  and  y = e^2 - z
"""
from lib.utility import start_time, end_time
from collections import defaultdict
start_time()


def is_square(n):
    s = int(n ** 0.5)
    return s*s == n


def find_smallest_xyz(square_limit):
    diffs = defaultdict(list)
    for i in range(1, square_limit - 1):
        for j in range(i + 1, square_limit, 1):
            diffs[j*j - i*i].append((j, i))

    for _, values in sorted(diffs.items()):
        for (e, f) in values:
            z = (e*e - f*f) // 2
            y = e*e - z

            if 2 * y in diffs:
                for (a, b) in diffs[2 * y]:
                    x = (a*a + b*b) // 2
                    test = (x + y, x - y, x + z, x - z, y + z, y - z)
                    if all(is_square(v) for v in test):
                        return x, y, z


x, y, z = find_smallest_xyz(square_limit=1000)
print('Solution:', x + y + z)
end_time()
