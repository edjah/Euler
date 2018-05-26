import time
from lib.utility import nCr_tbl
start = time.time()

def not_div7(n):
    return n % 7 != 0

ans = 0
for i in range(100):
    ans += sum(1 for _ in filter(not_div7, nCr_tbl(i)))

print("Solution:", ans)

end = time.time()
print(f"{1000 * (end - start):.3f} ms")
