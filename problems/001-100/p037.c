#include "lib/utility.h"


bool right_trunctable(unsigned n) {
    while (n > 0) {
        if (!miller_rabin(n)) {
            return false;
        }
        n /= 10;
    }
    return true;
}

int trunctable_search(int root) {
    int mult = pow(10, 1 + (int) log10(root));
    if (mult > 100000000) {
        return 0;
    }

    int ans = 0;
    for (int i = 1; i < 10; i++) {
        int k = mult * i + root;
        if (miller_rabin(k)) {
            if (right_trunctable(k)) {
                ans += k;
            }
            ans += trunctable_search(k);
        }
    }
    return ans;
}

int main(void) {
    start_time();

    // trunctable primes can only end in 3 or 7
    int tot = trunctable_search(3) + trunctable_search(7);
    printf("Solution: %d\n", tot);

    end_time();
}
