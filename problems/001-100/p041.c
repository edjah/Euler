#include "lib/utility.h"

int generate_pandigital(int x, bool used[], int ndigits) {
    bool all_used = true;
    int ans = 0;
    for (int i = 1; i <= ndigits; i++) {
        if (!used[i]) {
            all_used = false;
            used[i] = true;
            ans = MAX(ans, generate_pandigital(10*x + i, used, ndigits));
            used[i] = false;
        }
    }
    if (all_used && miller_rabin(x)) {
        ans = x;
    }
    return ans;
}

int main(void) {
    start_time();

    int ans = 0;
    bool used[10] = {false};
    for (int ndigits = 1; ndigits <= 9; ndigits++) {
        ans = MAX(ans, generate_pandigital(0, used, ndigits));
    }
    printf("Solution: %d\n", ans);

    end_time();
}
