#include "lib/utility.h"

int main(void) {
    start_time();

    int a = 1, b = 0, tmp = 0;
    int even = 0;
    while (a < 4000000) {
        if (a % 2 == 0) {
            even += a;
        }
        tmp = b;
        b = a;
        a += tmp;
    }
    printf("Solution: %d\n", even);

    end_time();
}
