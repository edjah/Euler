#include "lib/utility.h"
#include "lib/bignum.h"

int qsort_bignum_compare(const void* a, const void* b) {
    return bignum_compare(*((bignum**) a), *((bignum**) b));
}


int main(void) {
    start_time();

    bignum* arr[100 * 100];
    int size = 0;
    for (int a = 2; a <= 100; a++) {
        for (int b = 2; b <= 100; b++) {
            bignum* big_a = bignum_from_long(a);
            bignum* big_b = bignum_from_long(b);
            arr[size++] = bignum_mod_exp(big_a, big_b, NULL);
        }
    }

    qsort(arr, size, sizeof(bignum*), qsort_bignum_compare);

    int distinct = size;
    for (int i = 0; i < size - 1; i++) {
        if (bignum_compare(arr[i], arr[i + 1]) == 0) {
            distinct -= 1;
        }
    }
    printf("Solution: %d\n", distinct);


    end_time();
}
