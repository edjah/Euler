from time import perf_counter
import random
start = perf_counter()

grids = []
with open('p096_sudoku.txt', 'r') as f:
    grid = None
    for line in f:
        if line[0] == 'G':
            grid != None and grids.append(grid)
            grid = []
        else:
            grid.append([int(i) for i in line.strip()])
    grids.append(grid)


def possible(g, x, y):
    a, b = 3 * (x // 3), 3 * (y // 3)
    square = [g[a + i][b + j] for i in range(3) for j in range(3)]
    col = [g[i][y] for i in range(9)]
    row = g[x]
    return set(range(1, 10)) - set(row + col + square)

def sudoku_solve(G):
    n = len(G)
    blanks = [(i, j) for i in range(n) for j in range(n) if G[i][j] == 0]
    cycles = 0
    def dfs(idx, sol):
        nonlocal cycles
        cycles += 1

        if idx >= len(blanks):
            return sol

        a, b = blanks[idx]
        for i in possible(sol, a, b):
            sol[a][b] = i
            x = dfs(idx + 1, sol)
            if x != None:
                return x
            sol[a][b] = 0

        return None

    solution = dfs(0, G)
    if solution == None:
        print('Unable to find a solution')
    else:
        print('It took %d cycles' % cycles)

    return solution

ans = 0
for i, grid in enumerate(grids):
    print('Solving Grid #%d' % (i + 1), end='... ')
    g = sudoku_solve(grid)
    ans += g[0][0] * 100 + g[0][1] * 10 + g[0][2]

print('Solution:', ans)

end = perf_counter()
print(end - start, 'seconds to run')
