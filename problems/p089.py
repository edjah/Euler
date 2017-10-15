from time import clock
start = clock()

numerals = {
    'I': 1,
    'V': 5,
    'X': 10,
    'L': 50,
    'C': 100,
    'D': 500,
    'M': 1000
}

numeral_order = 'MDCLXVI'

def to_decimal(s):
    s = s.replace('IV', 'I' * 4)
    s = s.replace('IX', 'I' * 9)
    s = s.replace('XL', 'X' * 4)
    s = s.replace('XC', 'X' * 9)
    s = s.replace('CD', 'C' * 4)
    s = s.replace('CM', 'C' * 9)
    tot = sum(numerals[n] * s.count(n) for n in numerals)
    return tot

def to_numeral(x):
    i = 0
    s = ''
    while x > 0:
        k = numeral_order[i]
        if x >= numerals[k]:
            s += k
            x -= numerals[k]
        else:
            i += 1

    s = s.replace('DCCCC', 'CM')
    s = s.replace('CCCC', 'CD')
    s = s.replace('LXXXX', 'XC')
    s = s.replace('XXXX', 'XL')
    s = s.replace('VIIII', 'IX')
    s = s.replace('IIII', 'IV')

    return s


nums = []
orig_length = 0
with open('p089.txt') as f:
    for line in f:
        l = line.rstrip()
        orig_length += len(l)
        nums.append(to_decimal(l))

new_length = 0
for n in nums:
    new_length += len(to_numeral(n))

print('Original length:', orig_length)
print('Minimal length:', new_length)
print('Chars saved:', orig_length - new_length)

end = clock()
print(end - start, 'seconds to run')
