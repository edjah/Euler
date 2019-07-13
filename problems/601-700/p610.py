import numpy as np
from lib.utility import start_time, end_time
start_time()

numerals = [
    ("M", 1000, 0.14), ("CM", 900, 0.14 * 0.14),
    ("D", 500, 0.14), ("CD", 400, 0.14 * 0.14),
    ("C", 100, 0.14), ("XC", 90, 0.14 * 0.14),
    ("L", 50, 0.14), ("XL", 40, 0.14 * 0.14),
    ("X", 10, 0.14), ("IX", 9, 0.14 * 0.14),
    ("V", 5, 0.14), ("IV", 4, 0.14 * 0.14),
    ("I", 1, 0.14), ('#', float('-inf'), 0.02)
]


def to_numeral(n):
    result = ""
    for numeral, value, _ in numerals:
        while n > 0 and n >= value:
            n -= value
            result += numeral

    return result


def parse_roman_numeral(s):
    pos = 0
    total = 0

    while pos != len(s):
        for numeral, value, _ in numerals:
            while s.startswith(numeral, pos):
                total += value
                pos += len(numeral)
    return total


valid_follow_ups = {
    '': {'I', 'V', 'X', 'L', 'C', 'D', 'M'},
    'M': {'I', 'V', 'X', 'L', 'C', 'D', 'M'},
    'CM': {'I', 'V', 'X', 'L', 'C', 'D'},
    'D': {'I', 'V', 'X', 'L', 'C'},
    'CD': {'I', 'V', 'X', 'L'},
    'C': {'I', 'V', 'X', 'L', 'C'},
    'XC': {'I', 'V'},
    'L': {'I', 'V', 'X'},
    'XL': {'I', 'V'},
    'X': {'I', 'V', 'X'},
    'IX': set(),
    'V': {'I'},
    'IV': set(),
    'I': {'I', 'X'},
}

for i in range(1, 5):
    valid_follow_ups['M' * i] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'}

for i in range(1, 4):
    valid_follow_ups['C' * i] = {'I', 'V', 'X', 'L', 'C'}
valid_follow_ups['C' * 4] = {'I', 'V', 'X', 'L'}

for i in range(1, 4):
    valid_follow_ups['X' * i] = {'I', 'V', 'X'}
valid_follow_ups['X' * 4] = {'I', 'V'}

for i in range(1, 4):
    valid_follow_ups['I' * i] = {'I'}
valid_follow_ups['I' * 4] = set()


def is_minimal(s, char):
    return to_numeral(parse_roman_numeral(s + char)) == s + char


def is_minimal(s, char):
    if len(s) >= 2 and s[-1] == s[-2]:
        i = 0
        while s[-i - 1] == s[-1]:
            i += 1
        return char in valid_follow_ups[s[-i:]]

    return char in valid_follow_ups[s[-2:]]


probs = {s: 0.14 for s in ['I', 'V', 'X', 'L', 'C', 'D', 'M']}
probs['#'] = 0.02


keys = list(probs.keys())
p = list(probs.values())
samples = iter(list(np.random.choice(keys, size=10 ** 6, p=p)))


def trial():
    s = ''

    while True:
        char = next(samples)
        if char == '#':
            break

        if not is_minimal(s, char):
            continue
        s += char

    return parse_roman_numeral(s)


# total = 0
# for num_trials in range(1, 10 ** 100):
#     try:
#         total += trial()
#     except StopIteration:
#         break

# print(num_trials, 'trials |', total / num_trials)

print(is_minimal('I', 'X'))

end_time()
