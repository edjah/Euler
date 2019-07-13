from lib.utility import start_time, end_time
start_time()

max_base = 100
max_exp = 25

digit_power_sum_numbers = set()

for base in range(max_base):
    for exp in range(max_exp):
        n = base ** exp
        digit_sum = sum(int(i) for i in str(n))
        if digit_sum == base and n >= 10:
            digit_power_sum_numbers.add(n)

a = sorted(digit_power_sum_numbers)
print('Solution:', a[29])

end_time()
