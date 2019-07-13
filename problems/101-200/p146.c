#include "lib/utility.h"

#define NUM_INCRS 6
int valid_increments[] = {1, 3, 7, 9, 13, 27};


bool is_valid_incr(int v) {
    for (int i = 0; i < NUM_INCRS; ++i) {
        if (v == valid_increments[i]) {
            return true;
        }
    }
    return false;
}


bool ensure(ubigint n) {
    ubigint k = n * n;
    for (int i = 0; i < NUM_INCRS; ++i) {
        if (!miller_rabin(k + valid_increments[i])) {
            return false;
        }
    }
    return true;
}


bool consec_ensure(ubigint n) {
   ubigint k = n * n;
   for (int i = 1; i < 28; i += 2) {
        if (!is_valid_incr(i) && miller_rabin(k + i)) {
            return false;
        }
   }
   return true;
}


int main() {
    start_time();
    int total = 0;
    int limit = 150 * 1e6;

    for (int n = 10; n < limit; n += 10) {
        int r = n % 210;
        if (r != 10 && r != 80 && r != 130 && r != 200) {
            continue;
        }

        if (ensure(n) && consec_ensure(n)) {
            total += n;
        }
    }

    printf("Solution: %d\n", total);
    end_time();
}
