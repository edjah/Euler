#include "lib/utility.h"
#define LIMIT 200000


int main(void) {
    start_time();


    int factors[LIMIT] = {0};
    int count = 0;
    for (int i = 2; i < LIMIT; i++) {
        if (factors[i] == 0) {
            count = 0;
            for (int j = i; j < LIMIT; j += i) {
                factors[j] += 1;
            }
        } else if (factors[i] == 4) {
            count += 1;
            if (count == 4) {
                printf("Solution: %d\n", i - 3);
                break;
            }
        } else {
            count = 0;
        }
    }

    end_time();
}
