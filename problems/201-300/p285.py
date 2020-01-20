from lib.utility import start_time, end_time
import numpy as np
start_time()


def cdf(x, k):
    # These formulas were obtained from a bunch of mathematica bs...
    # together, they give the CDF of (ka + 1)^2 + (kb + 1)^2 using
    # the convolution integral. I probably should have thought a bit more about
    # this...
    def lo(x):
        a = 2*np.sqrt(x - 1)
        b = x*np.arcsin(1 / np.sqrt(x))
        c = x*np.arctan(np.sqrt(x - 1))
        return (2 - a - b + c) / (2 * k**2)

    def hi(x):
        a = 2 * (k+1) * np.sqrt(x - (k+1)**2)
        b = x*(np.pi/2 - np.arctan((k + 1) / np.sqrt(x - (k+1)**2)))
        c = x*np.arcsin((k + 1) / np.sqrt(x))
        return (1 + k) * (a - b + c) / (2*k**2 * (k + 1))

    if x < 2:
        return 0

    switch_point = 1 + (k+1) ** 2
    if x < switch_point:
        return lo(x)

    return hi(x) - (hi(switch_point) - lo(switch_point))


result = 0
for k in range(1, 10 ** 5 + 1):
    prob = cdf((k + 0.5)**2, k) - cdf((k - 0.5)**2, k)
    result += k * prob
print(f'Solution: {result:.5f}')

end_time()
