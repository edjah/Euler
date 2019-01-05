#include "lib/utility.h"


int main(void) {
    start_time();

    int count[1001] = {0};

    for (int a = 1; a < 1000; a++) {
        for (int b = a + 1; b < 1000; b++) {
            int c = sqrt(a*a + b*b);
            if (a + b + c > 1000) {
                break;
            }
            if (a*a + b*b == c*c) {
                count[a + b + c] += 1;
            }
        }
    }

    int max_perim = 0;
    int max_count = 0;
    for (int p = 0; p <= 1000; p++) {
        if (count[p] > max_count) {
            max_count = count[p];
            max_perim = p;
        }
    }
    printf("Solution: %d\n", max_perim);

    end_time();
}
