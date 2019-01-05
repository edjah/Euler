#include "lib/utility.h"

int divs[7] = {2, 3, 5, 7, 11, 13, 17};

long permute(long res, bool used[], int len) {
    if (len == 10) {
        return res;
    }

    long ans = 0;
    for (int i = 0; i < 10; i++) {
        if (!used[i] && (i > 0 || len > 0)) {
            long k = 10 * res + i;
            if (len >= 3 && (k % 1000) % divs[len - 3] != 0) {
                continue;
            }
            used[i] = true;
            ans += permute(k, used, len + 1);
            used[i] = false;
        }
    }
    return ans;
}


int main(void) {
    start_time();

    bool used[10] = {false};
    printf("Solution: %li\n", permute(0, used, 0));

    end_time();
}
