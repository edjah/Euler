#include "lib/utility.h"
#include "lib/bignum.h"

int main(void) {
    start_time();

    bignum* ans = BIGNUM_ZERO;
    bignum* modulo = bignum_from_long(10000000000);
    for (int i = 1; i <= 1000; i++) {
        bignum* x = bignum_from_long(i);
        ans = bignum_add(ans, bignum_mod_exp(x, x, modulo));
    }

    ans = bignum_mod(ans, modulo);
    printf("Solution: %s\n", bignum_to_string(ans));

    end_time();
}
