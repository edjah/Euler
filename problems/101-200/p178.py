from lib.utility import start_time, end_time, memoize
start_time()

max_chars = 40


@memoize
def dfs(curr_digit, num_chars_used, missing_digits):
    if num_chars_used == max_chars:
        return 0

    count = 1 if missing_digits == () else 0

    for next_char in (curr_digit - 1, curr_digit + 1):
        if 0 <= next_char <= 9:
            next_missing = tuple(d for d in missing_digits if d != next_char)
            count += dfs(next_char, num_chars_used + 1, next_missing)

    return count


count = 0
for start_char in range(1, 10):
    missing_digits = tuple(d for d in range(10) if d != start_char)
    count += dfs(start_char, 0, missing_digits)

print('Solution:', count)
end_time()
