N = 80
with open("p082.txt", "r") as f:
    l = f.readlines()
l = [x.split(",") for x in l]
l = [[int(i) for i in j] for j in l]

d = [[[None, None, None] for i in range(N)] for j in range(N)]
for i in range(N):
    d[i][N - 1][0] = l[i][N - 1]

def D(i, j, k):
    if i >= N or j >= N or i < 0 or j < 0:
        return float('inf')

    if d[i][j][k] != None:
        return d[i][j][k]

    if k == 0:
        d[i][j][k] = l[i][j] + min(D(i + 1, j, 1), D(i, j + 1, 0), D(i - 1, j, 2))
    elif k == 1:
        d[i][j][k] = l[i][j] + min(D(i + 1, j, 1), D(i, j + 1, 0))
    elif k == 2:
        d[i][j][k] = l[i][j] + min(D(i, j + 1, 0), D(i - 1, j, 2))

    return d[i][j][k]

print(min(D(i, 0, 0) for i in range(N)))
