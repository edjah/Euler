from lib.utility import start_time, end_time, memoize
start_time()

num_sides = 12
desired_tot = 70
top_size = 10
num_dice = 20


@memoize
def count(remaining_rolls, top):
    if remaining_rolls == 0:
        return sum(top) == desired_tot

    ans = 0
    for i in range(1, num_sides + 1):
        if len(top) != top_size:
            new_top = tuple(sorted((i,) + top))
        else:
            new_top = top
            if i > new_top[0]:
                new_top = tuple(sorted((i,) + new_top[1:]))

        if sum(new_top) > desired_tot:
            break
        ans += count(remaining_rolls - 1, new_top)

    return ans


ans = count(num_dice, ())
print('Solution:', ans)

end_time()
