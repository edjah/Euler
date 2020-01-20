/*
 By mathematica, we get that the equation can be solved for c to obtain:

         (1 + a)^2 * (8a - 1)
     c = ---------------------
                 27b^2

    - we need the numerator to be divisible by 27:
        => a must be equal to 2 mod 3

    - b^2 must be a divisor of num/27. we can look at the factorization of
        => we can look at the factors of num/27 to generate candidates for b?
*/
#include "lib/utility.hh"

using namespace std;

long method1(long limit) {
    long count = 0;
    for (long a = 1; a <= limit; ++a) {
        for (long b = 1; b <= limit - a; ++b) {
            long num = (1 + a) * (1 + a) * (8*a - 1);
            long den = 27 * b*b;
            long c = num / den;
            if (num % den == 0 && c > 0 && a + b + c <= limit) {
                count += 1;
            }
        }
    }

    return count;
}

long solve_for_a(long num, bool& is_good) {
    // based on some long formula from mathematica
    double x = cbrt(27 + 32*num + 8*sqrt(27*num + 16*num*num));
    long a = round((-5 + 9/x + x) / 8);

    if ((1 + a) * (1 + a) * (8*a - 1) == num) {
        is_good = true;
    }
    is_good = false;
    return a;
}

long method2(long limit) {
    long count = 0;
    for (long a = 2; a <= limit; a += 3) {
        for (long b = 1; b <= limit - a; ++b) {
            long num = (1 + a) * (1 + a) * (8*a - 1);
            long den = 27 * b*b;
            long c = num / den;
            if (num % den == 0 && c > 0 && a + b + c <= limit) {
                count += 1;
            }
        }
    }

    return count;
}


long method3(long limit) {
    auto factors = prime_factors_table(limit * 8 / 3 + 3);

    long count = 0;
    // for (long a = 2; a <= limit; a += 3) {
    //     for (long b = 1; b <= limit - a; ++b) {
    //         long num = (1 + a) * (1 + a) * (8*a - 1);
    //         long den = 27 * b*b;
    //         long c = num / den;
    //         if (num % den == 0 && c > 0 && a + b + c <= limit) {
    //             // fprintf(stderr, "%li/%li | %li %li\n", num, den, a, solve_for_a(num));
    //             count += 1;
    //         }
    //     }
    // }

    return count;
}


int main() {
    start_time();

    // long limit = 110000000;
    long limit = 1000;
    // long limit = 10000;




    // long count = method1(limit);
    long count = method2(limit);
    // method2(limit);
    // long count = method3(limit);


    // for n = 10000: Solution: 1632
    // for n = 20000: Solution: 3312
    // for n = 40000: Solution: 6714
    printf("Solution: %li\n", count);

    end_time();
}
