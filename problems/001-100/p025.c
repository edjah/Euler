#include "lib/utility.h"
#define MAX_DIGITS 128
#include "lib/bignum.h"

int main(void) {
    start_time();

    bignum* big10 = bignum_from_long(10);
    bignum* big999 = bignum_from_long(999);
    bignum* target = bignum_mod_exp(big10, big999, NULL);

    bignum* curr = BIGNUM_ONE;
    bignum* prev = BIGNUM_ZERO;

    int idx = 1;
    while (bignum_compare(curr, target) < 0) {
        bignum* tmp = curr;
        curr = bignum_add(curr, prev);
        prev = tmp;
        idx += 1;
    }
    printf("Solution: %d\n", idx);

    end_time();
}
