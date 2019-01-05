#include "lib/utility.h"

double log10_nCr(int n, int r) {
    double ans = 0;
    r = MIN(r, n - r);
    for (int i = 0; i < r; i++) {
        ans += log10(n - i) - log10(i + 1);
    }
    return ans;

}

int main(void) {
    start_time();

    int count = 0;
    for (int n = 1; n <= 100; n++) {
        for (int r = 1; r < n; r++) {
            if (log10_nCr(n, r) > 6) {
                count += 1;
            }
        }
    }
    printf("Solution: %d\n", count);

    end_time();
}
