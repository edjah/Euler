from lib.utility import start_time, end_time
from lib.prime import read_primes, miller_rabin
from itertools import permutations
start_time()

prime_set = set(read_primes(10 ** 6))


def get_possible_primes():
    digits = '123456789'
    k_digit_primes = [[] for i in range(0, 10)]
    for k in range(1, 10):
        for p in permutations(digits, k):
            x = int(''.join(p))
            if (k < 6 and x in prime_set) or miller_rabin(x):
                k_digit_primes[k].append(str(x))

    return k_digit_primes


def build_pandigital_sets():
    k_digit_primes = get_possible_primes()
    solutions = set()
    seen = set()

    def find_solutions(acc, remaining_digits):
        if acc in seen or remaining_digits < 0:
            return

        if remaining_digits == 0:
            solutions.add(acc)
            return

        seen.add(acc)
        for digits in range(1, remaining_digits + 1):
            for prime in k_digit_primes[digits]:
                set_string = ''.join(acc) + prime
                if len(set_string) != len(set(set_string)):
                    continue

                new_acc = tuple(sorted(acc + (prime,)))
                find_solutions(new_acc, remaining_digits - digits)

    find_solutions((), 9)
    return solutions


prime_sets = build_pandigital_sets()
print('Solution:', len(prime_sets))


end_time()
