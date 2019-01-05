#include "lib/utility.h"
#include "lib/bignum.h"


int main(void) {
    start_time();

    bignum* pow = bignum_from_long(1000);
    bignum* ans = bignum_mod_exp(BIGNUM_TWO, pow, NULL);
    char* s = bignum_to_string(ans);

    int tot = 0;
    for (int i = 0, n = strlen(s); i < n; i++) {
        tot += s[i] - '0';
    }
    printf("Solution: %d\n", tot);

    end_time();
}
