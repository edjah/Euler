from random import randint

prime_list = None
prime_set = set()
miller_rabin_nums = [2, 3, 5, 7, 11, 13, 17]
large_miller_rabin_nums = [19, 23, 29, 31, 37, 41]


def init(n):
    global prime_list, prime_set
    if n <= 10 ** 8:
        prime_list = read_primes(n)

    if prime_list is None:
        print('Using sieve instead of precomputed primes')
        prime_list = prime_sieve(n)

    prime_set = set(prime_list)
    return prime_list


def try_composite(a, d, n, s):
    x = pow(a, d, n)
    if x == 1 or x == n - 1:
        return False
    for i in range(s):
        if x == n - 1:
            return False
        x = pow(x, 2, n)
    return True


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

    # deterministic optimization!
    if k > 13 and n < 3317044064679887385961981:
        for i in miller_rabin_nums:
            if i != n and try_composite(i, d, n, s):
                return False
        if n >= 341550071728321:
            for i in large_miller_rabin_nums:
                if try_composite(i, d, n, s):
                    return False
        return True
    else:
        for i in range(k):
            if try_composite(randint(2, n - 2), d, n, s):
                return False

    return True


def rand_prime(k):
    if k < 2:
        raise ValueError("Cannot have a prime less than 2")
    n = randint(2, k)
    while not miller_rabin(n, 25):
        n = randint(2, k)
    return n


def read_primes(n):
    primes = []
    try:
        with open('lib/primes.txt', 'r') as f:
            for line in f:
                a = int(line)
                if a > n:
                    break
                primes.append(a)
        return primes
    except FileNotFoundError:
        return None


def prime_sieve(n):
    # https://stackoverflow.com/questions/2068372/fastest-way-to-list-all-primes-below-n-in-python/3035188#3035188
    """ Input n>=6, Returns a list of primes, 2 <= p < n """
    correction = n % 6 > 1
    n = [n, n - 1, n + 4, n + 3, n + 2, n + 1][n % 6]
    sieve = [True] * (n // 3)
    sieve[0] = False
    for i in range(1 + int(n ** 0.5) // 3):
        if sieve[i]:
            k = (3 * i + 1) | 1
            m1 = 1 + (n//6 - (k * k)//6 - 1) // k
            m2 = 1 + (n//6 - (k*k + 4*k - 2*k*(i & 1))//6 - 1) // k
            sieve[(k * k) // 3::2 * k] = [False] * m1
            sieve[(k*k + 4*k - 2*k*(i & 1)) // 3::2 * k] = [False] * m2

    tail = [(3 * i + 1) | 1 for i in range(1, n // 3 - correction) if sieve[i]]
    return [2, 3] + tail


def prime_factors_table(n):
    tbl = [[] for i in range(n + 1)]
    for i in range(2, n + 1):
        if tbl[i] == []:
            for j in range(i, n + 1, i):
                k = j
                while k % i == 0:
                    tbl[j].append(i)
                    k //= i
    return tbl


def prime_factors(n):
    if n in prime_set:
        return [n]
    facs = []
    i = 0
    while n > 1:
        if n % prime_list[i] == 0:
            n //= prime_list[i]
            facs.append(prime_list[i])
        else:
            i += 1
    return facs


def totient(n):
    facs = set(prime_factors(n))
    tot = n
    for x in facs:
        tot *= 1 - 1/x
    return int(tot)


def totient_table(n):
    phi = [0] * (n + 1)
    phi[1] = 1
    for i in range(2, n + 1):
        if phi[i] == 0:
            phi[i] = i - 1
            j = 2
            while i * j <= n:
                if phi[j] == 0:
                    j += 1
                    continue
                q, f = j, i - 1
                while q % i == 0:
                    f, q = f * i, q // i
                phi[i * j] = f * phi[q]
                j = j + 1
    return phi


if __name__ == "__main__":
    from utility import start_time, end_time

    start_time()
    # x = prime_sieve(974)
    # print(x)
    x = prime_factors_table(1000000)
    end_time()
