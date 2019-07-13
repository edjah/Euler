from lib.utility import start_time, end_time, subsets
start_time()


def is_special(s):
    for x in subsets(s):
        for y in subsets(s - set(x)):
            if len(x) == len(y) == 0:
                continue
            a, b = sum(x), sum(y)
            if len(x) < len(y) and a >= b:
                return False
            if len(y) < len(x) and b >= a:
                return False
            if a == b:
                return False
    return True


total = 0
with open('files/p105_sets.txt', 'r') as f:
    for line in f:
        s = set(int(i) for i in line.split(','))
        if is_special(s):
            total += sum(s)

print('Solution:', total)
end_time()
