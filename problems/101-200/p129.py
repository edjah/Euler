from lib.utility import start_time, end_time
start_time()


def A(n):
    k = 1
    repunit = 1

    while repunit != 0:
        repunit = (10 * repunit + 1) % n
        k += 1
    return k


# start the search at the limit because A(n) <= n
# due properties to properties of modular arithmetic
n = limit = 10 ** 6
while n % 2 == 0 or n % 5 == 0 or A(n) < limit:
    n += 1

print('Solution:', n)
end_time()
