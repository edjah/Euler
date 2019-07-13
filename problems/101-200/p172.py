from lib.utility import start_time, end_time, product
from math import factorial
start_time()


def count(max_len, curr_len, digit, counts):
    if digit > 9 or counts[-1] > 3:
        return 0

    if curr_len >= max_len:
        counts = counts[:]
        counts[0] -= 1
        return factorial(max_len) // product(factorial(i) for i in counts)

    res = count(max_len, curr_len + 1, digit, counts[:-1] + [counts[-1] + 1])
    res += count(max_len, curr_len, digit + 1, counts + [0])
    return res


ans = 9 * count(17, 0, 0, [1])
print('Solution:', ans)

end_time()
