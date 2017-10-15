from time import clock

def time_function(f, *args):
    start = clock()
    f(*args)
    end = clock()
    return end - start

def nCr(n, k):
    ans = 1
    for i in range(min(k, n - k)):
        ans = (ans * (n - i)) // (i + 1)
    return ans

def nCr_tbl(n):
    tbl = [1] + [0] * n
    for i in range(n):
        tbl[i + 1] = (tbl[i] * (n - i)) // (i + 1)
    return tbl

if __name__ == '__main__':
    x = nCr_tbl(10)
    print(x)
    print(time_function(nCr_tbl, 100000))
