#include "lib/utility.h"

int main(void) {
    start_time();

    long num = 600851475143;
    int p = 2;
    long limit = (long) sqrt(num);

    while (num > 1 && p <= limit) {
        if (num % p == 0) {
            num /= p;
        } else {
            p += 1;
        }
    }

    if (p < limit) {
        printf("Solution: %d\n", p);
    } else {
        printf("Solution: %li\n", num);
    }

    end_time();
}
