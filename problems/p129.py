from time import perf_counter
start = perf_counter()

def gcd(a, b):
    while b != 0:
        a, b = b, a % b
    return a

def R(n):
    return int('1' * n)

def A(n):
    k = 1
    while R(k) % n != 0:
        k += 1
    return k

a = A(41111)
print(a)



end = perf_counter()
print(end - start, 'seconds to run')
