from random import randint

def miller_rabin(n, k=25):
    if n == 2 or n == 3:
        return True
    if n % 2 == 0 or n < 2:
        return False

    s = 0
    d = n - 1
    while d % 2 == 0:
        d //= 2
        s += 1

    def try_composite(a):
        x = pow(a, d, n)
        if x == 1 or x == n - 1:
            return False
        for i in range(s):
            if x == n - 1:
                return False
            x = pow(x, 2, n)
        return True

    for i in range(k):
        if try_composite(randint(2, n - 2)):
            return False

    return True

def rand_prime(k):
    if k < 2:
        raise ValueError("Cannot have a random prime less than 2")
    n = randint(2, k)
    while not miller_rabin(n, 25):
        n = randint(2, k)
    return n


def sieve_array(n):
    A = [True] * (n + 1)
    q = int(n ** 0.5) + 1
    for i in range(2, q):
        if A[i]:
            for j in range(i * i, n, i):
                A[j] = False
    primes = []
    for i in range(2, n):
        if A[i]:
            primes.append(i)
    return primes

if __name__ == "__main__":
    from time import clock
    t1 = clock()

    print(rand_prime(2**31))

    t2 = clock()
    print(t2 - t1, "seconds")
