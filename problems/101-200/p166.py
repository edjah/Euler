from time import perf_counter
start = perf_counter()

def works(M):
    n = len(M)
    goal = sum(M[0])

    # checking diagonals
    if sum(M[i][i] for i in range(n)) != goal:
        return False
    if sum(M[-i - 1][i] for i in range(n)) != goal:
        return False

    # checking rows and columns
    for i in range(n):
        if sum(M[i]) != goal:
            return False
        if sum(M[j][i] for j in range(n)) != goal:
            return False
    return True



def criss_cross(size):
    cells = size * size
    complements = [[] for i in range(9 * size + 1)]
    def rec(acc):
        if len(acc) >= size:
            complements[sum(acc)].append(acc)
            return
        for i in range(10):
            rec(acc + (i,))
    rec(())

    for group in complements:
        print(len(group))



    print(len(complements))

    # return rows

print(criss_cross(4))

end = perf_counter()
print(end - start, 'seconds to run')
