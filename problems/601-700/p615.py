import time
import heapq
import lib.prime as prime
from tqdm import trange
from collections import defaultdict

start = time.time()
primes = prime.init(1000000) + [1]

N = 10 ** 6
mod = 123454321

init = defaultdict(int)
init[-1] = float('inf')
init[0] = N

heap = []
heapq.heappush(heap, (1, init))

seen = set()

for _ in range(N - 1):
    val, num_repr = heapq.heappop(heap)
    for k, v in num_repr.items():
        new_num_repr = num_repr.copy()
        if v > 1:
            new_num_repr[k] -= 1
        else:
            del new_num_repr[k]

        new_num_repr[k + 1] += 1
        new_val = val * primes[k + 1] / primes[k]

        if new_val not in seen:
            seen.add(new_val)
            heapq.heappush(heap, (new_val, new_num_repr))

ans = 1
for k, v in heap[0][1].items():
    if k != -1:
        ans *= pow(primes[k], v, mod)

print(sorted(heap[0][1].items()))
print("Solution:", ans % mod)

end = time.time()
print(f"{(end - start):.3f} sec")
