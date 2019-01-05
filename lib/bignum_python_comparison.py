from utility import time_function
NUM_OPS = 1000000


@time_function
def benchmark_string_parsing():
    a = "-812732189301259872132801938217365123021143218752189320129381"
    for i in range(NUM_OPS):
        int(a)


@time_function
def benchmark_to_string():
    a = -812732189301259872132801938217365123021143218752189320129381
    for i in range(NUM_OPS):
        str(a)


# 21 ms overhead (from empty for loop)
@time_function
def benchmark_compare():
    a = -812732189301259872132801938217365123021143218752189320129381
    for i in range(NUM_OPS):
        a < a
        pass


# 21 ms overhead (from empty for loop)
@time_function
def benchmark_add():
    a = 812732189301259872132801938217365123021143218752189320129381
    x = 0
    for i in range(NUM_OPS):
        x += a
        pass


@time_function
def benchmark_subtract():
    a = 812732189301259872132801938217365123021143218752189320129381
    x = 0
    for i in range(NUM_OPS):
        x -= a


@time_function
def benchmark_mult():
    a = 812732189301259872132801938217365123021143218752189320129381
    b = 812732189301259872132801938217365123021143218752189320129382
    for i in range(NUM_OPS):
        a * b


@time_function
def benchmark_div():
    a = 812732189301259872132801938217365123021143218752189320129381
    b = 17181273218930125987210193821736512302114321875218931
    for i in range(NUM_OPS):
        a // b


@time_function
def benchmark_mod_exp():
    return
    a = 812732189301259872132801938217365123021143218752189320129381
    for i in range(NUM_OPS):
        pow(a, a, a)


benchmark_string_parsing()
benchmark_to_string()
benchmark_compare()
benchmark_add()
benchmark_subtract()
benchmark_mult()
benchmark_div()
benchmark_mod_exp()
