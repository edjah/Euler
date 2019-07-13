from lib.utility import start_time, end_time
start_time()


def is_palindromic(n):
    s = str(n)
    return s == s[::-1]


palindromic_sum_numbers = set()
limit = 10 ** 8
sqrt_limit = 1 + int(limit ** 0.5)

for start in range(1, sqrt_limit):
    total = start ** 2
    for i in range(start + 1, sqrt_limit):
        total += i ** 2
        if total >= limit:
            break
        if is_palindromic(total):
            palindromic_sum_numbers.add(total)

print('Solution:', sum(palindromic_sum_numbers))
end_time()
