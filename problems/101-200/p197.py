from lib.utility import start_time, end_time
start_time()


def f(x):
    return int(pow(2, 30.403243784 - x**2)) * pow(10, -9)


un = -1
for n in range(10000):
    un = f(un)

print(f'Solution: {un + f(un):.9f}')
end_time()
