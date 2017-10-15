import itertools
from time import perf_counter

start = perf_counter()


def expressions(digits):
    strings = []

    def expr(s, digits):
        if len(digits) == 0:
            strings.append(s)
        elif len(digits) == 1:
            expr(s + digits[0], '')
        else:
            for d in digits:
                new_digits = digits.replace(d, '')
                for o in '+-*/':
                    expr(s + d + o, new_digits)

    expr('', digits)

    targets = set()

    def add_parens(s):
        n = len(s)
        for i in range(0, n - 2, 2):
            for j in range(i + 3, n + 1, 2):
                k = '{}({}){}'.format(s[0:i], s[i:j], s[j:])
                try:
                    x = eval(k)
                    if x > 0 and x == int(x):
                        targets.add(int(x))
                except:
                    pass

    for s in strings:
        add_parens(s)
    for maxrange in range(1, max(targets)):
        if maxrange not in targets:
            break
    return maxrange


best = (0, '0000')
t = 0
for a, b, c, d in itertools.combinations(range(10), 4):
    dig = '%d%d%d%d' % (a, b, c, d)
    x = expressions(dig)
    print((a, b, c, d), '=', x)
    if x > best[0]:
        best = (x, dig)

print('Solution:', best)


end = perf_counter()
print(end - start, 'seconds to run')

