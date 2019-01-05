#include "lib/utility.h"


bool is_perm(int a, int b) {
    int digit_counts[10] = {0};

    while (a > 0) {
        digit_counts[a % 10] += 1;
        a /= 10;
    }

    while (b > 0) {
        digit_counts[b % 10] -= 1;
        b /= 10;
    }

    for (int i = 0; i < 10; i++) {
        if (digit_counts[i] != 0) {
            return false;
        }
    }
    return true;
}


int main(void) {
    start_time();

    int n = 1;
    while (true) {
        bool flag = true;
        for (int i = 2; i <= 6; i++) {
            if (!is_perm(n, n * i)) {
                flag = false;
                break;
            }
        }
        if (flag) {
            break;
        }
        n += 1;
    }
    printf("Solution: %d\n", n);

    end_time();
}
