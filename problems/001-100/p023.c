#include "lib/utility.h"
#define LIMIT 28123


int has_abundant_sum[LIMIT];
int divisor_sum_tbl[LIMIT];
int abundant[LIMIT];
int abundant_size;


void populate_divisor_sum_tbl() {
    for (int i = 1; i < LIMIT; i++) {
        for (int j = i + i; j < LIMIT; j += i) {
            divisor_sum_tbl[j] += i;
        }
    }
}


int main(void) {
    start_time();

    populate_divisor_sum_tbl();

    for (int i = 1; i < LIMIT; i++) {
        if (divisor_sum_tbl[i] > i) {
            abundant[abundant_size++] = i;
        }
    }

    for (int i = 0; i < abundant_size; i++) {
        for (int j = i; j < abundant_size; j++) {
            if (abundant[i] + abundant[j] >= LIMIT) {
                break;
            }
            has_abundant_sum[abundant[i] + abundant[j]] = 1;
        }
    }

    int tot = 0;
    for (int i = 0; i < LIMIT; i++) {
        if (!has_abundant_sum[i]) {
            tot += i;
        }
    }
    printf("Solution: %d\n", tot);

    end_time();
}
