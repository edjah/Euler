#include "lib/utility.hh"
#include "lib/bignum.hh"

int main(void) {
    start_time();

    Bignum modulus = 10000000000L;
    Bignum answer = (Bignum(2).pow(7830457, modulus) * 28433 + 1) % modulus;
    printf("Solution: %li\n", answer.to_long());

    end_time();
}

