#include "lib/utility.hh"
#include "lib/bignum.hh"

#define NUM_LYCHREL_TRIALS 50

bool is_lychrel(Bignum b) {
    for (int i = 0; i < NUM_LYCHREL_TRIALS; ++i) {
        std::string str = b.to_string();
        std::string rev_str(str.rbegin(), str.rend());

        if (i > 0 && str == rev_str) {
            return false;
        }
        b += Bignum(rev_str, 10);
    }

    return true;
}
int main(void) {
    start_time();
    int count = 0;
    for (int i = 1; i < 10000; ++i) {
        count += is_lychrel(i);
    }
    printf("Solution: %d\n", count);
    end_time();
}
