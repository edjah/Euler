#include "lib/utility.h"

int main(void) {
    start_time();

    long tot = 0;
    for (int i = 0; i < 1000; i++) {
        if (i % 3 == 0 || i % 5 == 0) {
            tot += i;
        }
    }
    printf("Solution: %li\n", tot);

    end_time();
}
