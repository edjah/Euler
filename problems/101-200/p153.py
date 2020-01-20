from lib.utility import start_time, end_time, gcd, lcm
start_time()


def sum_sols(a, b, limit):
    c = a*a + b*b
    interval = lcm(c // gcd(a, c), c // gcd(b, c))

    num_occurences = limit // interval
    if b == 0:
        return a * num_occurences
    else:
        return num_occurences * (2*a + b)
        # return 2 * a * num_occurences + b * num_occurences


# limit = 10 ** 5
limit = 1000

tot = 0

# for every n, that n appears as a solution limit // n times
for n in range(1, limit + 1):
    tot += (limit // n) * n


z = 0

for a in range(1, limit + 1):
    for b in range(a, limit + 1):
        if a*a + b*b > a * limit:
            break

        v = sum_sols(a, b, limit)
        tot += v

        if v != 0:
            print(a, b)
            z += 1
        # if sum_sols(a, b, limit) != 0:
        #     c = a*a + b*b
        #     interval = lcm(c // gcd(a, c), c // gcd(b, c))

        #     num_occurences = limit // interval
        #     print(a, b, '|', sum_sols(a, b, limit) // a)

# 1752541
print(z)
print(tot, tot / 1752541)


"""
scratch work
"""
# def find_primitive_sols(n):
#     sols = []
#     for a in range(1, n + 1):
#         for b in range(n + 1):
#             div = a*a + b*b
#             if n*a % div == 0 and n*b % div == 0:
#                 sols.append((a, b))
#                 if b != 0:
#                     sols.append((a, -b))

#     return sols



# from collections import defaultdict
# sol_set = defaultdict(list)


# for n in range(1, limit + 1):
#     print(n, '\n====', sep='')
#     for a, b in find_primitive_sols(n):
#         assert n*a % (a*a + b*b) == 0
#         assert n*b % (a*a + b*b) == 0

#         print(a, b)
#         sol_set[(a, b)].append(n)
#     print()


# print(len(sol_set))

# total_tot = 0
# my_total_tot = 0
# for (a, b), v in sol_set.items():
#     tot = len(v) * a
#     total_tot += tot
#     my_ans = sum_sols(a, b, limit)
#     my_total_tot += my_ans
#     print(f'({a}, {b}) => should be: {tot} | got: {my_ans}')


# print(f'Total tot should be: {total_tot}')
# print(f'My total tot is: {my_total_tot}')


# for a in range(1, 1000):
#     for b in range(a, 1000):

#         d = a*a + b*b

#         expected = [d * i for i in range(1, n // d + 1)]
#         got = sol_set[(a, b)]
#         if got == []:
#             break
#         # if expected == got:
#         #     print('I GOT IT RIGHT!')
#         # print('expected:', d, '|', expected)
#         # print('got:', got)

#         g = lcm(d // gcd(a, d), d // gcd(b, d))

#         should_be = [g*i for i in range(1, n // g + 1)]
#         assert(should_be == got), (a, b, should_be, got)


end_time()
