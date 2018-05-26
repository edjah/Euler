#include "lib/utility.h"


int main(void) {
    start_time();

    int n = 100;
    int sum = n * (n + 1) / 2;
    int sum_sq = n * (n + 1) * (2*n + 1) / 6;
    printf("Solution: %d\n", sum*sum - sum_sq);

    end_time();
}
