#include "lib/utility.h"

inline bool checks_out(int n) {
    int a = 1, b = 1, c = 1;
    while (c != 0) {
        int d = (a + b + c) % n;
        a = b, b = c, c = d;

        // remainders have looped without seeing a 0
        if (a == 1 && b == 1 && c == 1) {
            return true;
        }
    }
    return false;
}

int main() {
    start_time();

    int num_sols = 0;
    int n = 1;
    while (num_sols < 124) {
        n += 2;
        if (checks_out(n)) {
            num_sols++;
        }
    }
    printf("Solution: %d\n", n);

    end_time();
}
