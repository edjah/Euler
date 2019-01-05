#include "lib/utility.h"


int main(void) {
    start_time();

    int num_prod = 1;
    int den_prod = 1;

    for (int a = 10; a <= 99; a++) {
        for (int b = a + 1; b <= 99; b++) {
            int a1 = a / 10, a2 = a % 10;
            int b1 = b / 10, b2 = b % 10;
            if (a2 == 0 && b2 == 0) {
                continue;
            }
            if (a1 == b1 && a * b2 == b * b2) {
                num_prod *= a;
                den_prod *= b;
            } else if (a1 == b2 && a * b1 == b * a2) {
                num_prod *= a;
                den_prod *= b;
            } else if (a2 == b1 && a * b2 == b * a1) {
                num_prod *= a;
                den_prod *= b;
            } else if (a2 == b2 && a * b1 == b * a1) {
                num_prod *= a;
                den_prod *= b;
            }
        }
    }
    printf("Solution: %li\n", den_prod / gcd(num_prod, den_prod));

    end_time();
}
