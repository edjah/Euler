#include "lib/utility.h"
#define LIMIT 100000

int divisor_sum_tbl[LIMIT];

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
    int tot = 0;
    for (int i = 0; i < 10000; i++) {
        int a = divisor_sum_tbl[i];
        if (divisor_sum_tbl[a] == i && a != i) {
            tot += i;
        }
    }
    printf("Solution: %d\n", tot);

    end_time();
}
