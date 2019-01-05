#include "lib/utility.hh"

int main(void) {
    start_time();

    int count = 0;
    for (int den = 1; den <= 12000; ++den) {
        for (int num = 1 + den / 3; num < den; ++num) {
            if (num * 2 >= den) {
                break;
            }
            assert(num * 3 > den && num * 2 < den);
            count += (gcd(num, den) == 1);
        }
    }
    printf("Solution: %d\n", count);

    end_time();
}
