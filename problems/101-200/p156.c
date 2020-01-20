#include "lib/utility.h"

const long pow10[] = {
    1L, 10L, 100L, 1000L, 10000L, 100000L, 1000000L, 10000000L,
    100000000L, 1000000000L, 10000000000L, 100000000000L,
    1000000000000L, 10000000000000L, 100000000000000L, 1000000000000000L
};

int num_digits(unsigned long n) {
    if (n == 0) {
        return 1;
    }

    int count = 0;
    while (n > 0) {
        count += 1;
        n /= 10;
    }
    return count;
}

long f(long n, int d) {
    int size = num_digits(n) - 1;
    long count = pow10[size - 1] * size;
    long base = pow10[size];

    int i = 0;
    while (base > 0) {
        int curr_digit = n / base;
        if (curr_digit == d) {
            count += n % base + 1;
        } else if (curr_digit > d) {
            count += base;
        }

        count += (curr_digit - (i == 0)) * size * (base / 10);
        n %= base;
        base /= 10;
        size -= 1;
        i += 1;
    }

    return count;
}

inline int sign(long n) {
    return n > 0 ? 1 : (n < 0 ? -1 : 0);
}

long s(int d) {
    int last_sign = 0;
    long sum = 0;
    long last_sol = 0;
    const long step = 100000;

    for (long i = 0; i < 100000000000L; i += step) {
        int sgn = sign(f(i, d) - i);
        if (sgn != last_sign) {
            // backtrack. never start at the last solution to avoid duplicates
            for (long j = MAX(1 + last_sol, i - step); j <= i; ++j) {
                if (f(j, d) == j) {
                    sum += j;
                }
            }
            last_sol = i;
            last_sign = sgn;
        }
    }

    return sum;
}

int main() {
    start_time();

    long solution = 0;
    for (int d = 1; d < 10; ++d) {
        solution += s(d);
    }
    printf("Solution: %li\n", solution);

    end_time();
}
