#include "lib/utility.h"


int main(void) {
    start_time();

    for (int a = 1; a <= 333; a++) {
        for (int b = a + 1; b <= 1000; b++) {
            int c = 1000 - a - b;
            if (c <= b) {
                break;
            }
            else if (a*a + b*b == c*c) {
                printf("Solution: %d\n", a * b * c);
                end_time();
                return 0;
            }
        }
    }
}
