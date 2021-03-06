a = """
BBBBBW BWW
BBBBBW BWWW
BBBBBW BWWWW
BBBBBW BWWWWW
BBBBBWW BWWW
BBBBBWW BWWWW
BBBBW BBWW
BBBBW BBWWW
BBBBW BBWWWW
BBBBW BBWWWWW
BBBBW BW BWW
BBBBW BW BWWW
BBBBW BW BWWWW
BBBBW BWW
BBBBW BWW BWW
BBBBW BWW BWWW
BBBBW BWWW
BBBBW BWWWW
BBBBW BWWWWW
BBBBWW BBWWW
BBBBWW BBWWWW
BBBBWW BW BWWW
BBBBWW BWWW
BBBBWW BWWWW
BBBW BBW BWW
BBBW BBW BWWW
BBBW BBW BWWWW
BBBW BBWW
BBBW BBWW BW
BBBW BBWW BWW
BBBW BBWW BWWW
BBBW BBWWW
BBBW BBWWW BW
BBBW BBWWW BWW
BBBW BBWWWW
BBBW BBWWWW BW
BBBW BBWWWWW
BBBW BW BW BWW
BBBW BW BW BWWW
BBBW BW BWW
BBBW BW BWW BWW
BBBW BW BWWW
BBBW BW BWWWW
BBBW BWW
BBBW BWW BWW
BBBW BWW BWWW
BBBW BWWW
BBBW BWWWW
BBBW BWWWWW
BBBWW BBW BWW
BBBWW BBW BWWW
BBBWW BBWWW
BBBWW BBWWW BW
BBBWW BBWWWW
BBBWW BW BWWW
BBBWW BWWW
BBBWW BWWWW
BBBWWW BBW BWW
BBW BBW BW BWW
BBW BBW BW BWWW
BBW BBW BWW
BBW BBW BWW BWW
BBW BBW BWWW
BBW BBW BWWWW
BBW BBWW BW BWW
BBW BBWW BWW
BBW BBWW BWWW
BBW BBWWW BWW
BBW BW BW BW BWW
BBW BW BW BWW
BBW BW BW BWWW
BBW BW BWW
BBW BW BWW BWW
BBW BW BWWW
BBW BW BWWWW
BBW BWW
BBW BWW BWW
BBW BWW BWWW
BBW BWWW
BBW BWWWW
BBW BWWWWW
BBWW BW BWWW
BBWW BWWW
BBWW BWWWW
"""

b = """
BBW BW BW BW BWW
BBW BBW BW BWWW
BBW BBW BWW BWW
BBBW BW BW BWWW
BBBW BW BWW BWW
BBBW BBW BWWWW
BBBW BBWW BWWW
BBBBW BW BWWWW
BBBBW BWW BWWW
BBBBW BBWWWWW
BBBBWW BBWWWW
BBBBBW BWWWWW
BBBBBWW BWWWW
BBW BBW BW BWW
BBBW BW BW BWW
BBBW BBW BWWW
BBBW BBWW BWW
BBBBW BW BWWW
BBBBW BWW BWW
BBBBW BBWWWW
BBBBWW BBWWW
BBBBBW BWWWW
BBBBBWW BWWW
BBBW BBW BWW
BBBBW BW BWW
BBBBW BBWWW
BBBBBW BWWW
BBBBW BBWW
BBBBBW BWW
BBW BW BW BWWW
BBW BW BWW BWW
BBW BBW BWWWW
BBW BBWW BWWW
BBBW BW BWWWW
BBBW BWW BWWW
BBBW BBWWWWW
BBBWW BBWWWW
BBBBW BWWWWW
BBBBWW BWWWW
BBW BW BW BWW
BBW BBW BWWW
BBW BBWW BWW
BBBW BW BWWW
BBBW BWW BWW
BBBW BBWWWW
BBBWW BBWWW
BBBBW BWWWW
BBBBWW BWWW
BBW BBW BWW
BBBW BW BWW
BBBW BBWWW
BBBBW BWWW
BBBW BBWW
BBBBW BWW
BBW BW BWWWW
BBW BWW BWWW
BBBW BWWWWW
BBBWW BWWWW
BBW BW BWWW
BBW BWW BWW
BBBW BWWWW
BBBWW BWWW
BBW BW BWW
BBBW BWWW
BBBW BWW
BBW BWWWWW
BBWW BWWWW
BBW BWWWW
BBWW BWWW
BBW BWWW
BBW BWW
"""


def process(s):
    return sorted(l.strip() for l in s.strip().split('\n'))


a = process(a)
b = process(b)

for g in set(a) - set(b):
    print(g)
