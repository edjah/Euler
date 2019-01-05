#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <sys/time.h>
#include "bignum.hh"

double tstamp() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return (double) tv.tv_sec + tv.tv_usec / 1e6;
}

Bignum rand_bignum(int ndigits) {
    std::string s = (rand() % 2 == 0) ? "" : "-";
    for (int i = 0; i < ndigits; ++i) {
        s += std::to_string(rand() % 1000000000);
    }
    return Bignum(s);
}

void output_line(const Bignum& a, const std::string& op, const Bignum& b,
                 const Bignum& result) {
    printf("(%s %s %s) == %s\n",
           a.to_string().c_str(), op.c_str(), b.to_string().c_str(),
           result.to_string().c_str());
}

void test_correctness() {
    std::vector<Bignum> nums;

    for (int i = 0; i < 1000; ++i) {
        Bignum a = rand_bignum(1 + rand() % 100);
        Bignum b = rand_bignum(1 + rand() % 100);
        Bignum c = rand_bignum(1 + rand() % 100);

        // comparison
        output_line(a, "<", b, a < b);
        output_line(a, "<=", b, a <= b);
        output_line(a, ">", b, a > b);
        output_line(a, ">=", b, a >= b);
        output_line(a, "==", b, a == b);
        output_line(a, "!=", b, a != b);

        // arithmetic
        output_line(a, "+", b, a + b);
        output_line(a, "-", b, a - b);
        output_line(a, "*", b, a * b);
        output_line(a, "//", b, a / b);
        output_line(a, "%", b, a % b);

        // exponentiation. ensure that b and c are positive
        b = b.abs();
        c = c.abs();
        printf("pow(%s, %s, %s) == %s\n",
               a.to_string().c_str(), b.to_string().c_str(),
               c.to_string().c_str(),
               a.pow(b, c).to_string().c_str());

        nums.push_back(a);
        nums.push_back(b);
        nums.push_back(c);
    }

    std::sort(nums.begin(), nums.end(), Bignum::compare);
    for (size_t i = 1; i < nums.size(); ++i) {
        output_line(nums[i - 1], "<=", nums[i], nums[i - 1] <= nums[i]);
    }
}

void generate_test_file(int num_lines) {
    std::ofstream outfile("test_data.txt");
    for (int i = 0; i < num_lines; ++i) {
        Bignum a = rand_bignum(1 + rand() % 100);
        Bignum b = rand_bignum(1 + rand() % 2);
        outfile << a.to_string() << " " << b.to_string() << std::endl;
    }
}

std::pair<std::vector<std::string>, std::vector<long>> parse_data() {
    std::vector<std::string> strings;
    std::vector<long> numbers;

    std::ifstream infile("test_data.txt");
    std::string str;
    std::string num;

    while (infile >> str >> num) {
        strings.push_back(str);
        numbers.push_back(stol(num));
    }

    return std::make_pair(strings, numbers);
}

void benchmark_string_parsing(std::vector<std::string>& strings,
                              std::vector<Bignum>& result) {
    for (const auto& s : strings) {
        result.push_back(Bignum(s));
    }
}

void benchmark_long_parsing(std::vector<long>& numbers,
                            std::vector<Bignum>& result) {
    for (const auto& n : numbers) {
        result.push_back(Bignum(n));
    }
}

void benchmark_compare(std::vector<Bignum>& bigs) {
    std::sort(bigs.begin(), bigs.end(), Bignum::compare);
}

void benchmark_addition(std::vector<Bignum>& bigs) {
    for (size_t i = 1; i < bigs.size(); ++i) {
        volatile Bignum res = bigs[i - 1] + bigs[i];
    }
}

void benchmark_subtraction(std::vector<Bignum>& bigs) {
    for (size_t i = 1; i < bigs.size(); ++i) {
        volatile Bignum res = bigs[i - 1] - bigs[i];
    }
}

void benchmark_multiplication(std::vector<Bignum>& bigs) {
    for (size_t i = 1; i < bigs.size(); ++i) {
        volatile Bignum res = bigs[i - 1] * bigs[i];
    }
}

void benchmark_division(std::vector<Bignum>& bigs) {
    for (size_t i = 1; i < bigs.size(); ++i) {
        volatile Bignum res = bigs[i - 1] / bigs[i];
    }
}

void benchmark_modulo(std::vector<Bignum>& bigs) {
    for (size_t i = 1; i < bigs.size(); ++i) {
        volatile Bignum res = bigs[i - 1] % bigs[i];
    }
}

void benchmark_pow(std::vector<Bignum>& bigs, size_t limit) {
    for (size_t i = 2; i < limit; ++i) {
        Bignum base = bigs[i - 2];
        Bignum exp = bigs[i - 1].abs();
        Bignum mod = bigs[i].abs();
        volatile Bignum res = base.pow(exp, mod);
    }
}

void benchmark_bignum_for_loop() {
    volatile int z;
    for (Bignum i = 0; i < 100000000; i += 1) {
        z = 0;
    }
    (void) z;
}

void benchmark_bignum_while_loop() {
    volatile int z;
    Bignum i = 0;
    while (i != 100000000) {
        z = 0;
        i += 1;
    }
    (void) z;
}

void performance_tests() {
    double t0 = tstamp();
    auto [strings, numbers] = parse_data();
    double t1 = tstamp();
    printf("Loading data: %.3f sec\n", t1 - t0);

    std::vector<Bignum> small_bigs;
    benchmark_long_parsing(numbers, small_bigs);
    double t2 = tstamp();
    printf("Long parsing: %.3f sec\n", t2 - t1);

    std::vector<Bignum> large_bigs;
    benchmark_string_parsing(strings, large_bigs);
    double t3 = tstamp();
    printf("String parsing: %.3f sec\n", t3 - t2);

    benchmark_compare(small_bigs);
    double t4 = tstamp();
    printf("Small comparison: %.3f sec\n", t4 - t3);

    benchmark_compare(large_bigs);
    double t5 = tstamp();
    printf("Large comparison: %.3f sec\n", t5 - t4);

    benchmark_addition(small_bigs);
    double t6 = tstamp();
    printf("Small addition: %.3f sec\n", t6 - t5);

    benchmark_addition(large_bigs);
    double t7 = tstamp();
    printf("Large addition: %.3f sec\n", t7 - t6);

    benchmark_subtraction(small_bigs);
    double t8 = tstamp();
    printf("Small subtraction: %.3f sec\n", t8 - t7);

    benchmark_subtraction(large_bigs);
    double t9 = tstamp();
    printf("Large subtraction: %.3f sec\n", t9 - t8);

    benchmark_multiplication(small_bigs);
    double t10 = tstamp();
    printf("Small multiplication: %.3f sec\n", t10 - t9);

    benchmark_multiplication(large_bigs);
    double t11 = tstamp();
    printf("Large multiplication: %.3f sec\n", t11 - t10);

    benchmark_division(small_bigs);
    double t12 = tstamp();
    printf("Small division: %.3f sec\n", t12 - t11);

    benchmark_division(large_bigs);
    double t13 = tstamp();
    printf("Large division: %.3f sec\n", t13 - t12);

    benchmark_modulo(small_bigs);
    double t14 = tstamp();
    printf("Small modulo: %.3f sec\n", t14 - t13);

    benchmark_modulo(large_bigs);
    double t15 = tstamp();
    printf("Large modulo: %.3f sec\n", t15 - t14);

    benchmark_pow(small_bigs, small_bigs.size());
    double t16 = tstamp();
    printf("Small pow: %.3f sec\n", t16 - t15);

    benchmark_pow(large_bigs, std::min(small_bigs.size(), 100UL));
    double t17 = tstamp();
    printf("Large pow: %.3f sec\n", t17 - t16);

    benchmark_bignum_for_loop();
    double t18 = tstamp();
    printf("Bignum for loop: %.3f sec\n", t18 - t17);

    benchmark_bignum_while_loop();
    double t19 = tstamp();
    printf("Bignum while loop: %.3f sec\n", t19 - t18);
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s [-c | -g | -p]\n", argv[0]);
        return 1;
    }

    std::string mode(argv[1]);
    if (mode == "-c") {
        double t0 = tstamp();
        test_correctness();
        double t1 = tstamp();
        fprintf(stderr, "Testing correctness: %.3f sec\n", t1 - t0);
    } else if (mode == "-g") {
        double t0 = tstamp();
        generate_test_file(1000000);
        double t1 = tstamp();
        fprintf(stderr, "Generating test file: %.3f sec\n", t1 - t0);
    } else if (mode == "-p") {
        performance_tests();
    } else {
        fprintf(stderr, "Usage: %s [-c | -g | -p]\n", argv[0]);
        return 1;
    }
    return 0;
}
