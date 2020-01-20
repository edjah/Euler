"""
Based on the clever observation by Daniel Qu that:
    log product(uniform) = sum(exponential) = gamma
"""
from lib.utility import start_time, end_time
from scipy.stats import gamma
from math import log
start_time()

log_c_min = 0
log_c_max = 1e100

while log_c_max - log_c_min > 0.0001:
    log_c = (log_c_min + log_c_max) / 2

    prob = 1 - gamma.cdf(log_c, 10 ** 7)

    if prob < 0.25:
        log_c_max = log_c
    else:
        log_c_min = log_c

print('Solution:', round(log_c / log(10), 2))
end_time()
