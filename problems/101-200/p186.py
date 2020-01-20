from lib.utility import start_time, end_time
from lib.datastructures import UnionFind
from collections import deque
start_time()


prime_minister = 524287
num_users = 1000000


def lagged_fibonacci_generator():
    k = 1
    s = deque([], 55)
    while True:
        if 1 <= k <= 55:
            nxt = (100003 - 200003*k + 300007*k**3) % num_users
        else:
            nxt = (s[31] + s[0]) % num_users

        s.append(nxt)
        k += 1
        yield nxt


generator = lagged_fibonacci_generator()
num_calls = 0

uf = UnionFind(num_users)
while uf.num_children[uf.find(prime_minister)] < 0.99 * num_users:
    a, b = next(generator), next(generator)
    if a != b:
        uf.union(a, b)
        num_calls += 1


print('Solution:', num_calls)

end_time()
