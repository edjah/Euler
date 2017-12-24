from time import perf_counter
from prime import read_primes
from itertools import product
from functools import reduce
start = perf_counter()


primes = read_primes(1000)

def prod(a):
    return reduce(lambda x, y: x * y, a)


def find_sol(n, nprimes, max_count):
    nums = [2 * i for i in range(1, max_count + 1)]
    best_count, best_powers = float('inf'), None

    for powers in product(nums, repeat=nprimes):
        count = (prod(x + 1 for x in powers) + 1) // 2
        if count > n and count < best_count:
            best_count, best_powers = count, powers[::-1]

    if best_powers:
        tot = prod(primes[i] ** (p // 2) for i, p in enumerate(best_powers))
        return tot
    else:
        return None


target = 4 * 10 ** 6

answer = None

for max_count in range(1, 100):
    tmp_ans = None
    for nprimes in range(2, 100):
        x = find_sol(target, nprimes, max_count)
        if tmp_ans is None or x < tmp_ans:
            tmp_ans = x
        else:
            break

    if answer is None or tmp_ans < answer:
        answer = tmp_ans
    else:
        break

print(f"Solution: {answer}")

end = perf_counter()
print(f"{end - start:f} seconds to run")
