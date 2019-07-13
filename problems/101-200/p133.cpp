#include "lib/utility.hh"

constexpr long N = 1000000000000000000LLU;

bool test_prime(int p) {
    return p >= 7 && mod_exp(10, N, p) == 1;
}

int main(void) {
    start_time();
    long solution = 0;
    for (int p : get_primes(100000)) {
        if (!test_prime(p)) {
            solution += p;
        }
    }
    printf("Solution: %ld\n", solution);
    end_time();
}
