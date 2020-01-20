
def num(a):
    return (1 + a)**2 * (8*a - 1)


def den(b):
    return 27 * b**2


count = 0
for a in range(1, 1000):
    for b in range(1, 1000 - a):
        n = num(a)
        d = den(b)
        c = n // d
        if n % d == 0 and a + b + c <= 1000:
            print(n // 27, b)
            count += 1


print(count)
