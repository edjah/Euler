from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def can_force_win(n):
    if n == 0:
        return 0
    if n == 1:
        return 0
    if n == 2:
        return 1

    for i in range(n - 1):
        if i == 0 or i == 1:
            if not can_force_win(n - i - 2):
                return 1
        elif i == n - 2 or i == n - 3:
            if not can_force_win(i):
                return 1
        else:
            left = can_force_win(i)
            right = can_force_win(n - i - 2)

            # TODO
            if i % 2 == 0 and (n - i - 2) % 2 == 0 and left and right:
                return 1

    return 0


tot = 0
for i in range(1, 51):
    print(f'can_force_win({i}) = {can_force_win(i)}')
    tot += can_force_win(i)

print('Solution:', tot)

end_time()
