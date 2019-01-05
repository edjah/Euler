#include "lib/utility.h"


int main(void) {
    start_time();

    int prod = 1;
    int target = 1;

    for (int n = 1, d = 0; d < 1000001; n++) {
        int tmp = n;
        int len = log10(n) + 1;
        int bufsize = len;
        int buffer[20] = {};

        while (tmp > 0) {
            buffer[--len] = tmp % 10;
            tmp /= 10;
        }

        for (int i = 0; i < bufsize; i++) {
            d += 1;
            if (d % target == 0) {
                prod *= buffer[i];
                target *= 10;
            }
        }
    }

    printf("Solution: %d\n", prod);

    end_time();
}
