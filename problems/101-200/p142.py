from time import perf_counter
start = perf_counter()

lim = 2 * 10 ** 2
squares = [i ** 2 for i in range(1, lim * lim)]
square_set = set(squares)


diff_squares = set()
for i in range(lim - 1):
    for j in range(i + 1, lim):
        diff_squares.add(squares[j] - squares[i])

diff_squares = sorted(diff_squares)
for i in range(len(diff_squares) - 1):
    for j in range(i + 1, len(diff_squares)):
        z = diff_squares[i] // 2
        y = diff_squares[j] // 2
        if y - z in square_set and y + z in square_set:
            for x in range(y + 1, y + 10000):
                if x - y in square_set and x + y in square_set:
                    print('partial:', x , y, z)
                    if x - z in square_set and x + z in square_set:
                        print('full:', x, y, z)
                        import sys
                        sys.exit(0)

# limit = 10 ** 2
# for x in range(3, limit):
#     for y in range(2, x):
#         for z in range(1, y):
#             if test(x, y, z):
#                 print(x, y, z)



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
