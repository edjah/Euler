#include "lib/utility.h"


bool is_pentagonal(int n) {
    int k = (sqrt(24*n + 1) + 1) / 6;
    return k * (3*k - 1) == 2 * n;
}

int pent(int n) {
    return n * (3*n - 1) / 2;
}

int main(void) {
    start_time();

    for (int i = 1; ; i++) {
        int a = pent(i);
        for (int j = 1; j < i; j++) {
            int b = pent(j);
            if (is_pentagonal(a + b) && is_pentagonal(a - b)) {
                printf("Solution: %d\n", a - b);
                end_time();
                return 0;
            }
        }
    }
}
