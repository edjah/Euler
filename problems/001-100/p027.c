#include "lib/utility.h"

int test(int a, int b) {
    for (int n = 0; ; n++) {
        if (!miller_rabin(n*n + a*n + b)) {
            return n - 1;
        }
    }
}

int main(void) {
    start_time();

    int best_c = 0;
    int best_prod = 0;
    for (int b = 0; b <= 1000; b++) {
        if (miller_rabin(b)) {
            // this lower bound for `a` ensures: n^2 + an + b > 0
            for (int a = -2 * sqrt(b); a < 1000; a++) {
                int c = test(a, b);
                if (c > best_c) {
                    best_c = c;
                    best_prod = a * b;
                }
            }
        }
    }
    printf("Solution: %d\n", best_prod);

    end_time();
}
