from lib.utility import start_time, end_time, nCr_tbl
start_time()


def visualize(limit, mod):
    for i in range(limit):
        tbl = [n % mod for n in nCr_tbl(i)]
        line = ' '.join('0' if x == 0 else ' ' for x in tbl)
        print((limit - i) * ' ' + line)


def discrete_log(n, base):
    z = base
    count = 0
    while z <= n:
        z *= base
        count += 1
    return count


def count_divisible(n, mod=7):
    if n <= mod:
        return 0

    biggest_tri = mod ** discrete_log(n - 1, mod)
    depth = n // biggest_tri

    # counting the full triangles at the top
    big_width = biggest_tri - 1
    total = depth * (depth - 1) // 2 * big_width * (big_width + 1) // 2
    total += depth * (depth + 1) // 2 * count_divisible(biggest_tri, mod)

    # counting the partial triangles at the bottom
    extra_lines = n - depth * biggest_tri
    end_width = big_width - extra_lines
    partial_big = (big_width*(big_width + 1) - end_width*(end_width + 1)) // 2
    total += depth * partial_big
    total += (depth + 1) * count_divisible(extra_lines, mod)

    return total


n = 10 ** 9
total_nums = n * (n + 1) // 2
not_divisble = total_nums - count_divisible(n, 7)
print('Solution:', not_divisble)
end_time()
