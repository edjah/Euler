from lib.utility import start_time, end_time
start_time()


"""
n^(n) * (n-1)^(n-1) * ... * (1)^(1)
--------------------------------------
1^(n) * 2^(n-1) * ... * n^(1)
"""


def B(n):
    result = 1
    for i in reversed(range(1, n + 1)):
        exp = 2*i - n - 1
        print(i, exp)
        if exp >= 0:
            result *= i ** exp
        else:
            result //= i ** (-exp)

    return result


print(B(14))

end_time()
# 11:15 pm
