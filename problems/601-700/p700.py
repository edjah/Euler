"""
Based on a clever observation by Daniel Qu.

Keep track of the min remainder and max remainder as you iterate:

min_remainder + max_remainder < min_remainder -> new eulercoin guaranteed
min_remainder + max_remainder >= max_remainder -> new maximum guaranteed
"""
from lib.utility import start_time, end_time
start_time()


mod = 4503599627370517
start = 1504170715041707

min_remainder = max_remainder = start
total = start

while min_remainder != 0:
    tot = (min_remainder + max_remainder) % mod
    if tot < min_remainder:
        min_remainder = tot
        total += min_remainder
    elif tot >= max_remainder:
        max_remainder = tot
    else:
        assert False

print('Solution:', total)
end_time()
