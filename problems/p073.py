from time import clock
from fractions import Fraction as Frac
start = clock()

def fraction_range_count(D):
    onethird = Frac(1, 3)
    onehalf = Frac(1, 2)
    valid = []
    for d in range(2, D + 1):
        for n in range(d//3, d//2 + 1):
            f = Frac(n, d)
            if onethird < f < onehalf:
                valid.append(f)
    return len(set(valid))

print('Solution:', fraction_range_count(2000))
end = clock()
print(end - start, 'seconds to run')
