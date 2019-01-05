#include "lib/utility.h"


int main(void) {
    start_time();

    int n = 1001;
    int tot = 1;
    for (int k = 3; k <= n; k += 2) {
        tot += 4*k*k - 6*k + 6;
    }
    printf("Solution: %d\n", tot);

    end_time();
}
