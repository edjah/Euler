#include "lib/utility.h"
#define LIMIT 1000000

int prime_size;
int* primes;

int main(void) {
    start_time();

    primes = sieve(LIMIT, &prime_size);
    int max_length = 0;
    int max_ans = 0;
    for (int i = 0; i < prime_size; i++) {
        int curr_length = 0;
        int curr_tot = 0;
        int ans_tot = 0;
        int ans_length = 0;
        for (int j = i; j < prime_size && curr_tot < LIMIT; j++) {
            if (miller_rabin(curr_tot)) {
                ans_length = curr_length;
                ans_tot = curr_tot;
            }
            curr_length++;
            curr_tot += primes[j];
        }
        if (ans_length > max_length) {
            max_length = ans_length;
            max_ans = ans_tot;
        }
    }
    printf("Solution: %d\n", max_ans);

    end_time();
}
