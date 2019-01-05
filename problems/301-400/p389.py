from lib.utility import start_time, end_time


def mean_roll(n):
    return (n + 1) / 2


def var_roll(n):
    return (n * n - 1) / 12


def next_lvl(lvl, old_mean, old_variance):
    # Eve's law
    mean = mean_roll(lvl) * old_mean
    variance = (old_mean * var_roll(lvl)) + (mean_roll(lvl) ** 2 * old_variance)
    return mean, variance


def solve():
    mean, variance = 1, 0
    for lvl in (4, 6, 8, 12, 20):
        mean, variance = next_lvl(lvl, mean, variance)
    return mean, variance


start_time()
mean, variance = solve()
print(f'Mean: {mean:.4f} | Variance: {variance:.4f}')
end_time()
