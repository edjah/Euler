from lib.utility import start_time, end_time
from lib.prime import read_primes
start_time()

primes = read_primes(100)
max_exp = 10
max_num_primes = 100
min_num_sols = 4_000_000


def search(max_exp, num_primes=0, n=1, num_divisors=1):
    if (num_divisors + 1) // 2 > min_num_sols:
        return n
    elif num_primes >= max_num_primes:
        return float('inf')

    best_answer = float('inf')
    for exp in range(1, max_exp + 1):
        new_num_divisors = num_divisors * (1 + 2 * exp)
        new_n = n * primes[num_primes] ** exp
        answer = search(exp, num_primes + 1, new_n, new_num_divisors)
        best_answer = min(answer, best_answer)

    return best_answer


answer = search(max_exp)
print('Solution:', answer)
end_time()
