#include "lib/utility.h"

#define N 20000000
#define R 15000000

unsigned long prime_factor_sums[N + 1];

void compute_prime_factor_sum() {
    for (int i = 2; i <= N; i++) {
        if (prime_factor_sums[i] == 0) {
            for (int j = i; j <= N; j += i) {
                int k = j;
                while (k % i == 0) {
                    prime_factor_sums[j] += i;
                    k /= i;
                }
            }
        }
    }
}

unsigned long nCr_factor_sum(int n, int r) {
    unsigned long res = 0;
    for (int i = 0; i < MIN(r, n - r); i++) {
        res += prime_factor_sums[n - i];
        res -= prime_factor_sums[i + 1];
    }
    return res;
}

int main(void) {
    start_time();

    compute_prime_factor_sum();
    unsigned long ans = nCr_factor_sum(N, R);
    printf("Solution: %lu\n", ans);

    end_time();
}
