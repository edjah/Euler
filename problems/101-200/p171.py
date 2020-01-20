from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def total(n, d):
    """
    Return the sum (mod 10^9) of all numbers 0 <= x < 10*n
    such that the sum of the squares of each of their digits is equal to `d`
    """
    if n == 0 and d == 0:
        return (0, 1)
    elif n == 0:
        return (0, 0)

    new_tot, new_count = (0, 0)
    for i in range(0, 10):
        tot, count = total(n // 10, d - i*i)
        new_tot += i*n*count + tot
        new_count += count

    return (new_tot, new_count)


ans = 0
for i in range(1, 100):
    if i * i > 20 * 81:
        break
    tot, count = total(10 ** 19, i**2)
    ans += tot

print('Solution:', ans % 10**9)
end_time()
