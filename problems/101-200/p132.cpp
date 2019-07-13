#include "lib/utility.hh"

constexpr long N = 1000000000;

// R(n) = 0 mod p           =>     R(n) + 1 = 1 mod p
// R(n) = (10^n - 1) / 9    =>     R(n) + 1 = (10^n + 8) / 9
// 10^n mod p == 1          =>     R(n) + 1 = (1 + 8) / 9 = 1 mod p

bool test_prime(int p) {
    return p >= 7 && mod_exp(10, N, p) == 1;
}

int main(void) {
    start_time();

    long tot = 0;
    int count = 0;
    for (int p : get_primes(200000)) {
        if (test_prime(p)) {
            tot += p;
            if (++count == 40) {
                printf("Solution: %ld\n", tot);
                break;
            }
        }
    }

    end_time();
}
