from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def increasing(min_digit, num_digits):
    if num_digits <= 0:
        return 1

    count = 0
    for i in range(min_digit, 10):
        count += increasing(i, num_digits - 1)
    return count


def decreasing(max_digit, num_digits):
    return increasing(10 - max_digit - 1, num_digits)


total = 0
for d in range(1, 101):
    total += increasing(1, d) + decreasing(9, d) - 10

print('Solution:', total)
end_time()
