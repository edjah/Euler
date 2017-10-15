from time import perf_counter
start = perf_counter()


sols = set()
def gen_soln(ring, digits, line):
    if line == len(ring) - 1:
        ring[line][2] = ring[0][1]
        ring[line][0] = digits.pop()
        if sum(ring[line]) == sum(ring[0]):
            idx = ring.index(min(ring, key=lambda x: x[0]))
            ring = ring[idx:] + ring[:idx]
            sols.add(tuple(map(tuple, ring)))
        return

    for d1 in digits:
        for d3 in digits - {d1}:
            ring[line][0], ring[line][2] = d1, d3
            ring[line + 1][1] = d3
            if sum(ring[line]) != sum(ring[0]):
                continue

            gen_soln(ring, digits - {d1, d3}, line + 1)

digits = set(range(1, 10 + 1))
for d in digits:
    ring = [[0, d, 0]] + [[0, 0, 0] for i in range(4)]
    gen_soln(ring, digits - {d} , 0)

ans = 0
for sol in sols:
    string = ''.join(''.join(map(str, s)) for s in sol)
    if len(string) == 16 and int(string) > ans:
        ans = int(string)

print('Ans:', ans)
end = perf_counter()
print(end - start, 'seconds to run')
