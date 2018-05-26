from time import perf_counter
from lib.prime import read_primes, miller_rabin
from itertools import permutations
start = perf_counter()

prime_set = set(read_primes(10 ** 8))

def get_possible_primes():
    digits = '123456789'
    k_digit_primes = [[] for i in range(0, 10)]
    for k in range(1, 10):
        for p in permutations(digits, k):
            x = int(''.join(p))
            if (k < 9 and x in prime_set) or miller_rabin(x):
                k_digit_primes[k].append(x)

    t = 0
    for i in range(len(k_digit_primes)):
        print(i, '-', len(k_digit_primes[i]))
        t += len(k_digit_primes[i])
    return k_digit_primes


def verify_set(s):
    x = ''.join(str(i) for i in s)
    return len(set(x)) == len(x) == 9

def build_pandigital_sets(kd_primes):
    valid = set()
    seen = set()
    tot = 0
    def rec(acc, n):
        nonlocal tot
        if acc in seen:
            tot += 1
            return
        if n <= 0:
            verify_set(acc) and valid.add(acc)
            return
        seen.add(acc)
        for m in range(1, n + 1):
            for p in kd_primes[m]:
                if p in acc:
                    continue
                t = tuple(sorted(acc + (p,)))
                rec(t, n - m)

    rec((), 9)
    print('Size of seen:', tot)
    return valid

k_digit_primes = get_possible_primes()
prime_sets = build_pandigital_sets(k_digit_primes)

print('Solution:', len(prime_sets))

end = perf_counter()
print(end - start, 'seconds to run')
