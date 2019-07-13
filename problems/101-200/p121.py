from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def winning_prob(num_blues, turn, turn_limit):
    if turn > turn_limit:
        return num_blues > turn_limit // 2

    p = 1 / (turn + 1)
    pick_blue = winning_prob(num_blues + 1, turn + 1, turn_limit)
    pick_red = winning_prob(num_blues, turn + 1, turn_limit)
    return (p * pick_blue) + ((1 - p) * pick_red)


winning_prob = winning_prob(0, 1, 15)
print('Solution:', 1 // winning_prob)
end_time()
