#include "lib/utility.h"
#define LIMIT 1000000

bool test_prime(char digits[], bool replaced[], int len, int idx, char last) {
    if (idx == len) {
        int count = 0;
        for (int d = 0; d < 10; d++) {
            if (d == 0 && replaced[0]) {
                continue;
            }
            for (int j = 0; j < len; j++) {
                if (replaced[j]) {
                    digits[j] = '0' + d;
                }
            }
            if (miller_rabin(atoi(digits))) {
                count += 1;
            }
        }
        return count == 8;
    } else {
        replaced[idx] = true;
        bool check = (last == -1 || digits[idx] == last);
        if (check && test_prime(digits, replaced, len, idx + 1, digits[idx])) {
            return true;
        }

        replaced[idx] = false;
        if (test_prime(digits, replaced, len, idx + 1, last)) {
            return true;
        }
        return false;
    }
}

int main(void) {
    start_time();

    int size;
    int* primes = sieve(LIMIT, &size);

    bool replaced[10] = {false};
    char digits[10];

    for (int i = 0; i < size; i++) {
        sprintf(digits, "%d", primes[i]);
        int len = strlen(digits);
        if (test_prime(digits, replaced, len, 0, -1)) {
            printf("Solution: %d\n", primes[i]);
            break;
        }
    }

    end_time();
}
