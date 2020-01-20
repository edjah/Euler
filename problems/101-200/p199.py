from lib.utility import start_time, end_time
from math import pi, sin, cos, tan, sqrt
from collections import namedtuple
start_time()

Circle = namedtuple('Circle', ['cx', 'cy', 'r'])
Gap = namedtuple('Gap', ['circles', 'is_exterior'])

# initial radius of the 3 circles. arrived at with some binary search to
# estimate it and wolfram alpha to get the closed form
r1 = 2 * sqrt(3) - 3

c1 = Circle(cx=(1 - r1) * cos(3*pi / 6), cy=(1 - r1) * sin(3*pi / 6), r=r1)
c2 = Circle(cx=(1 - r1) * cos(7*pi / 6), cy=(1 - r1) * sin(7*pi / 6), r=r1)
c3 = Circle(cx=(1 - r1) * cos(11*pi / 6), cy=(1 - r1) * sin(11*pi / 6), r=r1)

gaps = [
    Gap([c1, c2, c3], False),
    Gap([c1, c2], True),
    Gap([c1, c3], True),
    Gap([c2, c3], True),
]


end_time()
