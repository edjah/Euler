from time import perf_counter
start = perf_counter()

lim = 10 ** 2
squares = [i ** 2 for i in range(1, lim)]
square_set = set(squares)

def test(x, y, z):
    if not (x > y > z > 0):
        return False
    v = [x + y, x - y, x + z, x - z, y + z, y - z]
    if any(i not in square_set for i in v):
        return False
    return True

for i in range(len(squares) - 4):
    for j in range(i + 2, len(squares) - 2, 2):
        for k in range(j + 2, len(squares), 2):
            zy = (squares[j] - squares[i]) // 2
            yz = (squares[j] + squares[i]) // 2

            xy = (squares[k] - squares[j]) // 2
            yx = (squares[k] + squares[j]) // 2

            xz = (squares[k] - squares[i]) // 2
            zx = (squares[k] + squares[i]) // 2

            # print(zy, zx)



# s[j] = y + z
# s[i] = y - z
#
# y = (s[j] + s[i]) / 2
# z = (s[j] - s[i]) / 2
#
#
#
print('Nah. Not that easy')

end = perf_counter()
print(end - start, 'seconds to run')
