#include "lib/utility.h"

int reverse(int i) {
    int res = 0;
    while (i > 0) {
        res = 10 * res + (i % 10);
        i /= 10;
    }
    return res;
}

int all_digits_are_odd(int i) {
    while (i > 0) {
        if (i % 2 == 0) {
            return false;
        }
        i /= 10;
    }
    return true;
}

int main() {
    start_time();
    int count = 0;
    for (int i = 1; i < 1000000000; ++i) {
        if (i % 10 != 0 && all_digits_are_odd(i + reverse(i))) {
            count += 1;
        }
    }
    printf("Solution: %d\n", count);
    end_time();
}
