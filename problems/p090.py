from time import perf_counter
from itertools import combinations
start = perf_counter()

dice = []
for x in combinations(range(10), 6):
    if 6 in x or 9 in x:
        dice.append(set(x + (6, 9)))
    else:
        dice.append(set(x))

squares = [(0, 1), (0, 4), (0, 9), (1, 6),
           (2, 5), (3, 6), (4, 9), (6, 4), (8, 1)]

count = 0
for i in range(len(dice) - 1):
    for j in range(i + 1, len(dice)):
        x, y = dice[i], dice[j]
        valid = all(a in x and b in y or b in x and a in y for a, b in squares)
        count += valid

print('Ans:', count)


end = perf_counter()
print(end - start, 'seconds to run')
