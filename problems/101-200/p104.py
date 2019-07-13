from lib.utility import start_time, end_time
from math import log10, sqrt
start_time()


def last_nine_digits_generator():
    modulus = 10 ** 9
    a, b = 1, 1
    while True:
        yield a
        a, b = b % modulus, (a + b) % modulus


def first_nine_digits_generator():
    log_phi = log10((1 + sqrt(5)) / 2)
    log_root_5 = log10(sqrt(5))

    n = 1
    while True:
        approx_log_fn = n * log_phi - log_root_5
        fractional = approx_log_fn - int(approx_log_fn)
        yield int(10 ** (9 + fractional))
        n += 1


front_gen = first_nine_digits_generator()
back_gen = last_nine_digits_generator()
for k, (front, back) in enumerate(zip(front_gen, back_gen), 1):
    front = ''.join(sorted(str(front)[:9]))
    back = ''.join(sorted(str(back)[-9:]))
    if front == back == '123456789':
        break

print('Solution:', k)
end_time()
