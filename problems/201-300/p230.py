from lib.utility import start_time, end_time
start_time()

A = "1415926535897932384626433832795028841971693993751058209749445923078164062862089986280348253421170679"
B = "8214808651328230664709384460955058223172535940812848111745028410270193852110555964462294895493038196"


def kth_char(k, idx, lengths):
    if idx == 0:
        return A[k - 1]
    elif idx == 1:
        return B[k - 1]

    a = lengths[idx - 2]
    if k <= a:
        return kth_char(k, idx - 2, lengths)
    else:
        return kth_char(k - a, idx - 1, lengths)


ans = 0
lengths = [len(A), len(B)]

for n in range(18):
    k = (127 + 19*n) * 7**n

    while lengths[-1] < k:
        lengths.append(lengths[-1] + lengths[-2])

    ans += 10**n * int(kth_char(k, len(lengths) - 1, lengths))

print('Solution:', ans)
end_time()
