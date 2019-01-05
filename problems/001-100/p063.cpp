#include "lib/utility.hh"
#include "lib/bignum.hh"


int main(void) {
    start_time();

    int count = 0;
    for (int base = 1; base < 10; ++base) {
        for (size_t pow = 1; pow < 100; ++pow) {
            count += (Bignum(base).pow(pow).to_string().size() == pow);
        }
    }
    printf("Solution: %d\n", count);

    end_time();
}
