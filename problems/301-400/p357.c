#include "lib/utility.h"

#define N 100000000
bool is_prime[N + 1];

int test(int n) {
    for (int d = 1, s = sqrt(n); d <= s; ++d) {
        if (n % d == 0 && !is_prime[d + n/d]) {
            return 0;
        }
    }
    return 1;
}

int main() {
    start_time();

    int size;
    const int* primes = read_primes_less_than(N, &size);
    for (int i = 0; i < size; ++i) {
        is_prime[primes[i]] = 1;
    }

    long sol = 0;
    for (long n = 0; n < N; ++n) {
        sol += test(n) * n;
    }

    printf("Solution: %li\n", sol);
    end_time();
}
