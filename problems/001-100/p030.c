#include "lib/utility.h"

int digit_fifth_power_sum(int i) {
    int tot = 0;
    while (i > 0) {
        tot += pow(i % 10, 5);
        i /= 10;
    }
    return tot;
}

int main(void) {
    start_time();

    int limit = 5 * pow(9, 5);
    int tot = 0;
    for (int i = 2; i <= limit; i++) {
        if (digit_fifth_power_sum(i) == i) {
            tot += i;
        }
    }
    printf("Solution: %d\n", tot);

    end_time();
}
