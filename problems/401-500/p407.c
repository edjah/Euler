#include "lib/utility.h"

#define MAX_N 10000001

int sizes[MAX_N];
int tbl[MAX_N][24];

void generate_prime_factor_table() {
    for (int i = 2; i < MAX_N; i++) {
        if (sizes[i] == 0) {
            for (int j = i; j < MAX_N; j += i) {
                int k = j;
                while (k % i == 0) {
                    tbl[j][sizes[j]++] = i;
                    k /= i;
                }
            }
        }
    }
}

int M(int n) {
    int max = tbl[n][sizes[n] - 1];
    int best = 0;
    for (int a = n - max; a >= 0; a -= max) {
        if ((a * a) % n == a) {
            best = MAX(best, a);
        }
        if ((a*a + 2*a + 1) % n == a + 1) {
            best = MAX(best, a + 1);
        }
    }
    return best;
}

int main(void) {
    start_time();

    generate_prime_factor_table();

    long sol = 0;
    for (int i = 2; i < MAX_N; i++) {
        sol += M(i);
    }
    printf("Solution: %li\n", sol);

    end_time();
}
