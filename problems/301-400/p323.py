from lib.utility import start_time, end_time
start_time()


def expected_xor(bits):
    def prob(k):
        return (1 - 0.5 ** k) ** bits

    tot = 0
    for i in range(1, 10 ** 3):
        tot += i * (prob(i) - prob(i - 1))
    return tot


sol = expected_xor(32)
print(f'Solution: {sol:.10f}')
end_time()
