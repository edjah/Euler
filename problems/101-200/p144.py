"""
The equations describing the motion of the laser beam are:
x = x0 + cos(theta)*t
y = y0 + sin(theta)*t
4x^2 + y^2 = 100
Solve for t in terms of x0, y0, theta
"""
from lib.utility import start_time, end_time
import math
start_time()


def next_xy(x0, y0, theta):
    a = 1 / (4 + math.tan(theta) ** 2) / math.cos(theta)
    b1 = 4*x0 + y0*math.tan(theta)
    b2 = -4*x0 - y0*math.tan(theta)

    d = -math.cos(theta) ** 4
    e = -100 + y0**2 - 2*x0*y0*math.tan(theta)
    f = (-25 + x0**2) * math.tan(theta) ** 2
    g = 2 * math.sqrt(d * (e + f)) / math.cos(theta) ** 2

    # one of the t's is zero which basically says no movement
    t1 = -a * (b1 + g)
    t2 = a * (b2 + g)
    t = t1 if abs(t1) > abs(t2) else t2

    x = x0 + math.cos(theta)*t
    y = y0 + math.sin(theta)*t
    return x, y


def next_angle(x, y, theta):
    normal_angle = math.atan2(-4*x, y) + math.pi / 2
    diff = normal_angle - theta
    return (math.pi + normal_angle) + diff


x = 0
y = 10.1
theta = math.atan2(-9.6 - y, 1.4 - x)
num_bounces = 0

while True:
    x, y = next_xy(x, y, theta)
    theta = next_angle(x, y, theta)

    if abs(x) <= 0.01 and y > 9.999:
        break
    num_bounces += 1

print(f'Solution: {num_bounces}')
end_time()
