from lib.utility import start_time, end_time
start_time()


def is_bouncy(n):
    a = [int(i) for i in str(n)]
    up = down = False
    for i in range(len(a) - 1):
        up = up or a[i] < a[i + 1]
        down = down or a[i] > a[i + 1]
    return up and down


bounce = 0
tot = 1
while bounce / tot < 0.99:
    bounce += is_bouncy(tot)
    tot += 1

end_time()
