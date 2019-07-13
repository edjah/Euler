from lib.utility import start_time, end_time
start_time()

a = curr = 1777
mod = 10 ** 8
for i in range(1885):
    curr = pow(a, curr, mod)

print('Solution:', curr)
end_time()
