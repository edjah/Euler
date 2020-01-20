from lib.utility import start_time, end_time, memoize
start_time()


@memoize
def gen_complete(remaining_b, remaining_w):
    if remaining_w == 0 and remaining_b == 0:
        return {()}

    results = set()
    for b in range(remaining_b + 1):
        for w in range(remaining_w + 1):
            if b + w == 0:
                continue

            head = ("B"*b + "W"*w,)
            for tail in gen_complete(remaining_b - b, remaining_w - w):
                results.add(tuple(sorted(head + tail)))

    return results


@memoize
def gen_my_way(min_b, min_mb, max_mb, remaining_b, min_w, min_mw, remaining_w):
    if remaining_w == 0 and remaining_b == 0:
        return {()}

    if (min_b + min_mb > remaining_b) or (min_w + min_mw > remaining_w):
        return set()

    results = set()

    for b in range(min_b, remaining_b + 1):
        for w in range(min_w, remaining_w + 1):
            for mw in range(min_mw, remaining_w - w + 1):
                for mb in range(min_mb, remaining_b - b + 1):
                    if max(mb, mw) > 0 and min(mb, mw) == 0:
                        continue

                    if mb + mw + b + w == 0:
                        continue

                    head = tuple(g for g in ["B"*b, "W"*w, "B"*mb + "W"*mw] if g)
                    for tail in gen_my_way(b, mb, max_mb, remaining_b - b - mb, w, mw, remaining_w - w - mw):
                        results.add(tuple(sorted(head + tail)))

                # for mb in reversed(range(0, max_mb + 1)):
                #     if max(mb, mw) > 0 and min(mb, mw) == 0:
                #         continue

                #     if mb + mw + b + w == 0:
                #         continue

                #     head = tuple(g for g in ["B"*b, "W"*w, "B"*mb + "W"*mw] if g)
                #     for tail in gen_my_way(b, min_mb, mb, remaining_b - b - mb, w, mw, remaining_w - w - mw):
                #         results.add(tuple(sorted(head + tail)))

    return results


num_black = 6
num_white = 6
groups1 = gen_complete(num_black, num_white)
groups2 = gen_my_way(0, 0, num_black, num_black, 0, 0, num_white)

assert groups2 - groups1 == set()

k = set()
for g in sorted(groups1 - groups2):
    k.add(tuple(sorted(x for x in g if x.count('B') > 0 and x.count('W') > 0)))

for g in sorted(k):
    print(' ' + str(g).replace('\'', '').replace(',', '').replace('(', '').replace(')', ''))


print(f'Should have {len(groups1)} groups')
print(f'Am getting {len(groups2)} groups')


end_time()
