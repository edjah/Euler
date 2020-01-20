from lib.utility import start_time, end_time
start_time()


def fractran(seed, program):
    while True:
        for (a, b) in program:
            # if (seed * a) % b == 0:
            if seed % b == 0:
                seed = (seed * a) // b
                yield seed
                break
        else:
            return


program = [
    (17, 91), (78, 85), (19, 51), (23, 38), (29, 33),
    (77, 29), (95, 23), (77, 19), (1, 17),
    (11, 13), (13, 11), (15, 2), (1, 7), (55, 1)
]


m = 0
j = 0
seq = fractran(2, program)
for i in range(1, 100):
    s = next(seq)
    print(i, s)

    m = max(m, s)
    if s & (s - 1) == 0:
        j += 1
        print(i, '|', j, '|', len(bin(s)) - 3)

print(m, len(str(m)))

from lib.prime import init, prime_factors
init(100)

for p in sorted(set(sum(program, ()))):
    s = str(prime_factors(p)).replace('[', '{').replace(']', '}')
    print(f'[{p}] = {s},')

print(sorted(set([f for p in program for x in p for f in prime_factors(x)])))

end_time()



