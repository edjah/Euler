from collections import defaultdict
from time import perf_counter
start = perf_counter()



dir_mappings = [
    (1, 0),
    (0, -1),
    (-1, 0),
    (0, 1),
]

def simulate(num_moves, f=False):
    grid = defaultdict(int)
    x, y = 0, 0
    direction = 0

    moves = []

    for i in range(1, num_moves + 1):
        if grid[(x, y)] == 1:
            grid[(x, y)] = 0
            direction = (direction - 1) % 4
        else:
            grid[(x, y)] = 1
            direction = (direction + 1) % 4

        dx, dy = dir_mappings[direction]
        x += dx
        y += dy

        moves.append((dx, dy))

    return moves
    return sum(grid.values())


def guess(x):
    pass

x = 10 ** 6
s = simulate(x)

def find_cycle(eles):
    pass

print(s)

# print("x =", x)
# print("s =", s, " | s / x =", round(s / x, 3))

end = perf_counter()
print(f"{end - start:.4f} sec")
