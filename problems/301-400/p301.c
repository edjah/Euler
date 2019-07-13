#include "lib/utility.h"

#define limit (1 << 30)

unsigned X(unsigned n1, unsigned n2, unsigned n3) {
    return n1 ^ n2 ^ n3;
}

int main() {
    start_time();

    unsigned count = 0;
    for (unsigned n = 1; n <= limit; ++n) {
        count += X(n, 2*n, 3*n) == 0;
    }
    printf("Solution: %u\n", count);

    end_time();
}
