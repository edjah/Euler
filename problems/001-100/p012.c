#include "lib/utility.h"


int* sizes;
int** tbl;

int count_divisors(int n) {
    int prod = 1, count = 1, curr = 1;

    for (int i = 0; i < sizes[n]; i++) {
        if (tbl[n][i] == curr) {
            count += 1;
        } else {
            prod *= count;
            count = 2;
        }
        curr = tbl[n][i];
    }
    prod *= count;

    return prod;
}


int main(void) {
    start_time();

    tbl = prime_factors_tbl(20000, &sizes);

    long n = 0;
    int count;
    while (true) {
        n += 1;
        if (n % 2 == 0) {
            count = count_divisors(n / 2) * count_divisors(n + 1);
        } else {
            count = count_divisors((n + 1) / 2) * count_divisors(n);
        }
        if (count > 500) {
            break;
        }
    }

    printf("Solution: %li\n", n * (n + 1) / 2);

    end_time();
}

