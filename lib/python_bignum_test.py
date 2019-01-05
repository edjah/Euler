#!/usr/bin/python3.6
import sys
import time


def parse_data():
    strings, numbers = [], []
    with open("test_data.txt", "r") as fp:
        for line in fp:
            string, num = line.strip().split(" ")
            strings.append(string)
            numbers.append(int(num))
    return strings, numbers


def benchmark_string_parsing(strings, result):
    for s in strings:
        result.append(int(s))


def benchmark_long_parsing(numbers, result):
    for n in numbers:
        result.append(n)


def benchmark_compare(bigs):
    bigs.sort()


def benchmark_addition(bigs):
    for i in range(1, len(bigs)):
        bigs[i - 1] + bigs[i]


def benchmark_subtraction(bigs):
    for i in range(1, len(bigs)):
        bigs[i - 1] - bigs[i]


def benchmark_multiplication(bigs):
    for i in range(1, len(bigs)):
        bigs[i - 1] * bigs[i]


def benchmark_division(bigs):
    for i in range(1, len(bigs)):
        bigs[i - 1] / bigs[i]


def benchmark_modulo(bigs):
    for i in range(1, len(bigs)):
        bigs[i - 1] & bigs[i]


def benchmark_pow(bigs, limit):
    for i in range(2, limit):
        pow(bigs[i - 2], abs(bigs[i - 1]), abs(bigs[i]))


def benchmark_for_loop():
    for i in range(100000000):
        pass


def benchmark_while_loop():
    i = 0
    while i < 100000000:
        i += 1


def performance_tests():
    t0 = time.time()
    strings, numbers = parse_data()
    t1 = time.time()
    print(f"Loading data: {t1 - t0:.3f} sec")

    small_bigs = []
    benchmark_long_parsing(numbers, small_bigs)
    t2 = time.time()
    print(f"Long parsing: {t2 - t1:.3f} sec")

    large_bigs = []
    benchmark_string_parsing(strings, large_bigs)
    t3 = time.time()
    print(f"String parsing: {t3 - t2:.3f} sec")

    benchmark_compare(small_bigs)
    t4 = time.time()
    print(f"Small comparison: {t4 - t3:.3f} sec")

    benchmark_compare(large_bigs)
    t5 = time.time()
    print(f"Large comparison: {t5 - t4:.3f} sec")

    benchmark_addition(small_bigs)
    t6 = time.time()
    print(f"Small addition: {t6 - t5:.3f} sec")

    benchmark_addition(large_bigs)
    t7 = time.time()
    print(f"Large addition: {t7 - t6:.3f} sec")

    benchmark_subtraction(small_bigs)
    t8 = time.time()
    print(f"Small subtraction: {t8 - t7:.3f} sec")

    benchmark_subtraction(large_bigs)
    t9 = time.time()
    print(f"Large subtraction: {t9 - t8:.3f} sec")

    benchmark_multiplication(small_bigs)
    t10 = time.time()
    print(f"Small multiplication: {t10 - t9:.3f} sec")

    benchmark_multiplication(large_bigs)
    t11 = time.time()
    print(f"Large multiplication: {t11 - t10:.3f} sec")

    benchmark_division(small_bigs)
    t12 = time.time()
    print(f"Small division: {t12 - t11:.3f} sec")

    benchmark_division(large_bigs)
    t13 = time.time()
    print(f"Large division: {t13 - t12:.3f} sec")

    benchmark_modulo(small_bigs)
    t14 = time.time()
    print(f"Small modulo: {t14 - t13:.3f} sec")

    benchmark_modulo(large_bigs)
    t15 = time.time()
    print(f"Large modulo: {t15 - t14:.3f} sec")

    benchmark_pow(small_bigs, len(small_bigs))
    t16 = time.time()
    print(f"Small pow: {t16 - t15:.3f} sec")

    benchmark_pow(large_bigs, min(len(large_bigs), 100))
    t17 = time.time()
    print(f"Small pow: {t17 - t16:.3f} sec")

    benchmark_for_loop()
    t18 = time.time()
    print(f"For loop: {t18 - t17:.3f} sec")

    benchmark_while_loop()
    t19 = time.time()
    print(f"While loop: {t19 - t18:.3f} sec")


def check_correctness():
    while True:
        line = sys.stdin.readline()
        if not line:
            break

        line = line.strip()
        if eval(line) is not True:
            print("Failure on line:", line)
            break


if __name__ == "__main__":
    if len(sys.argv) != 2:
        print(f"Usage: {sys.argv[0]} [-c | -p]")
        sys.exit(1)

    if sys.argv[1] == "-c":
        check_correctness()
    elif sys.argv[1] == "-p":
        performance_tests()
    else:
        print(f"Usage: {sys.argv[0]} [-c | -p]")
        sys.exit(1)
