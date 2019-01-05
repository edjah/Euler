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

    int size;
    int* primes = sieve(10000, &size);

    for (int i = 0; i < size; i++) {
        if (primes[i] < 1000) {
            continue;
        }

        int a = primes[i];
        if (a == 1487) {
            continue;
        }

        int max_step = (10000 - a) / 2;
        for (int step = 1; step < max_step; step += 1) {
            if (miller_rabin(a + step) && miller_rabin(a + step * 2)) {
                if (is_perm(a, a + step) && is_perm(a, a + step * 2)) {
                    printf("Solution: %d%d%d\n", a, a + step, a + step * 2);
                }
            }
        }
    }

    end_time();
}
