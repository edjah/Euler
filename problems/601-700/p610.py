from time import clock
import random
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


def is_minimal(string):
    x = to_decimal(string)
    return to_numeral(x) == string

chars = ["I", "V", "X", "L", "C", "D", "M", "#"]
weights = [0.14] * 7 + [0.02]
char_weights = {k: v for k, v in zip(chars, weights)}

def trial(target=None):
    string = ""

    while True:
        x = random.random()
        for i in range(len(weights)):
            if x < weights[i]:
                string += chars[i]
                break
            else:
                x -= weights[i]

        if string[-1] == "#":
            string = string[:-1]
            break
        elif not is_minimal(string):
            string = string[:-1]

    if target is None:
        return to_decimal(string)
    else:
        return string == target


def _calc_prob(string):
    avail = list(chars)
    count = {c: 0 for c in avail}
    p = 1
    for c in string:
        p *= char_weights[c] / sum(char_weights[x] for x in avail)
        count[c] += 1


        if c == "V":
            avail = ["I", "#"]

        elif c == "L":
            avail = ["I", "V", "X", "#"]

        elif c == "D":
            avail = ["I", "V", "X", "L", "C", "#"]


        if c == "I":
            if count["I"] == 1:
                avail = ["I", "V", "X", "#"]
            elif count["I"] == 2:
                avail = ["I", "#"]
            elif count["I"] == 3:
                avail = ["#"]

        elif c == "X":
            if count["X"] == 1:
                avail = ["I", "V", "X", "L", "C", "#"]
            elif count["X"] == 2:
                avail = ["I", "V", "X", "#"]
            elif count["X"] == 3:
                avail = ["I", "V", "#"]
            elif count["X"] == 4:
                avail = ["I", "#"]


        elif c == "C":
            pass

        elif c == "M":
            pass


    return p


def calc_prob(string):
    avail = list(chars)

    count = {c: 0 for c in avail}


    if string[0] == "V":
        avail = ["I", "#"]
    elif string[0] == "L":
        avail = ["I", "V", "X", "#"]
    elif string[0] == "D":
        avail = ["I", "V", "X", "L", "C", "#"]
    elif string[0] == "I":
        avail = ["I", "V", "X", "#"]
    elif string[0] == "X":
        avail = ["I", "V", "X", "L", "C", "#"]
    elif string[0] in "CM":
        avail = ["I", "V", "X", "L", "C", "D", "M", "#"]

    count[string[0]] += 1


    p = 0.14

    for a, b in zip(string[:-1], string[1:]):
        if b not in avail:
            p *= 0

        p *= char_weights[b] / sum(char_weights[x] for x in avail)
        count[b] += 1

        if b == "V":
            if a != "I":
                avail = ["I", "#"]
            else:
                avail = ["#"]

        elif b == "L":
            if a != "X":
                avail = ["I", "V", "X", "#"]
            else:
                avail = ["I", "V", "#"]

        elif b == "D":
            if a != "C":
                avail = ["I", "V", "X", "L", "C", "#"]
            else:
                avail = ["I", "V", "X", "L", "#"]

        elif b == "I":
            if count["I"] == 1:
                avail = ["I", "V", "X", "#"]
            elif count["I"] == 2:
                avail = ["I", "#"]
            elif count["I"] == 3:
                avail = ["#"]

            if a != "I":
                avail = ["I", "#"]

        elif b == "X":
            if count["X"] == 1:
                avail = ["I", "V", "X", "L", "C", "#"]
            elif count["X"] == 2:
                avail = ["I", "V", "X", "#"]
            elif count["X"] == 3:
                avail = ["I", "V", "#"]
            elif count["X"] == 4:
                avail = ["#"]

            if a == "I":
                avail = ["#"]

        elif b == "C":
            if count["C"] == 1:
                avail = ["I", "V", "X", "L", "C", "D", "M", "#"]
            elif count["C"] == 2:
                avail = ["I", "V", "X", "L", "C", "#"]
            elif count["C"] == 3:
                avail = ["I", "V", "X", "L", "#"]
            elif count["C"] == 4:
                avail = ["I", "V", "#"]

            if a == "D":
                avail = []
            if a == "X":
                avail = ["I", "V", "#"]

        elif b == "M":
            if a == "C":
                avail = ["I", "V", "X", "L", "#"]

    return p




# tot = 0
# for i in range(10 ** 5):
    # tot += calc_prob(to_numeral(i) + "#") * i

# print(f"{tot:.8f}")

ntrials = 10 ** 4
target = "VIII"
x = sum(trial(target) for _ in range(ntrials))
print(f"Observed prob: {x / ntrials:.5f}")
print(f"Expected prob: {calc_prob(target + '#'):.5f}")

end = clock()
print(end - start, 'seconds to run')
