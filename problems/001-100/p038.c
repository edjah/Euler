#include "lib/utility.h"


bool check(int x, int n) {
    int digits[9] = {0};

    for (int i = 1; i <= n; i++) {
        int prod = x * i;
        while (prod > 0) {
            int d = prod % 10;
            prod /= 10;
            if (d == 0 || digits[d - 1]) {
                return false;
            }
            digits[d - 1] = 1;
        }
    }

    for (int i = 0; i < 9; i++) {
        if (!digits[i]) {
            return false;
        }
    }

    return true;
}


int concat_prod(int x, int n) {
    int res = 0;
    for (int i = 1; i <= n; i++) {
        int prod = x * i;
        res *= pow(10, 1 + (int) log10(prod));
        res += prod;
    }
    return res;
}


int main(void) {
    start_time();

    int max = 0;
    for (int n = 2; n < 10; n++) {
        int limit = pow(1000000000, 1.0 / n);
        for (int x = 1; x <= limit; x++) {
            if (check(x, n)) {
                max = MAX(max, concat_prod(x, n));
            }
        }
    }
    printf("Solution: %d\n", max);


    end_time();
}
