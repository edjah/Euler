#include "lib/utility.h"


int cycle_length(int d) {
    int n = 1;
    int nums[d + 1];
    int idx = 0;

    while (true) {
        if (n >= d) {
            n %= d;
            nums[idx++] = n;
        } else {
            n *= 10;
            if (n < d) {
                nums[idx++] = n;
            }
        }

        for (int i = 0; i < idx - 1; i++) {
            if (nums[i] == n) {
                return idx - i - 1;
            }
        }
    }
}

int main(void) {
    start_time();

    int best_cycle = 0;
    int best_num = 0;
    for (int d = 1; d < 1000; d++) {
        int c = cycle_length(d);
        if (c > best_cycle) {
            best_cycle = c;
            best_num = d;
        }
    }
    printf("Solution: %d\n", best_num);

    end_time();
}
