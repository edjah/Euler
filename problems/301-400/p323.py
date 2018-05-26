from time import perf_counter
start = perf_counter()

def expected_xor(bits):
    def prob(k):
        return (1 - 0.5 ** k) ** bits
    tot = 0
    for i in range(1, 10 ** 3):
        tot += i * (prob(i) - prob(i - 1))
    return tot

print('%.10f' % expected_xor(32))

end = perf_counter()
print(end - start, 'seconds to run')
