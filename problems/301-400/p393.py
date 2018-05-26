import time
start = time.time()

def adjacent(i, j, n):
    adj = []
    if i > 0:
        adj.append((i - 1, j))
    if i < n - 1:
        adj.append((i + 1, j))
    if j > 0:
        adj.append((i, j - 1))
    if j < n - 1:
        adj.append((i, j + 1))
    return adj



def f(n):
    grid = [[0] * n for _ in range(n)]
    horiz_edges = [[0] * (n - 1) for _ in range(n)]
    vert_edges = [[0] * n for _ in range(n - 1)]

    def dfs(idx):
        if idx == n ** 2:
            for g in horiz_edges:
                print(g)
            print()
            for g in vert_edges:
                print(g)
            print('----------------------------')
            return 1

        i, j = idx // n, idx % n

        ans = 0
        for x, y in adjacent(i, j, n):
            if not grid[x][y]:
                if x == i:
                    e = min(j, y)
                    if not horiz_edges[i][e]:
                        grid[x][y] = horiz_edges[i][e] = 1
                        ans += dfs(idx + 1)
                        grid[x][y] = horiz_edges[i][e] = 0
                elif y == j:
                    e = min(i, x)
                    if not vert_edges[e][j]:
                        grid[x][y] = vert_edges[e][j] = 1
                        ans += dfs(idx + 1)
                        grid[x][y] = vert_edges[e][j] = 0

        return ans

    return dfs(0)

ans = f(5)
print("Solution:", ans)

end = time.time()
print(f"{1000 * (end - start):.3f} ms")


''' f(6) == 207408 '''

"""
-------------
| 1 | 1 | 1 |
-------------
| 1 | 1 | 1 |
-------------
| 1 | 1 | 1 |
-------------

2 * (n - 1) * n


"""
