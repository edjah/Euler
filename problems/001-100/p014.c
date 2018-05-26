#include "lib/utility.h"


unsigned collatz_count(unsigned long n) {
    if (n == 1) {
        return 1;
    } else if (n % 2 == 0) {
        return 1 + collatz_count(n / 2);
    } else {
        return 1 + collatz_count(3*n + 1);
    }
}

int main(void) {
    start_time();

    int max_chain = 0;
    int max_num = 0;
    for (int i = 1; i < 1000000; i++) {
        int x = collatz_count(i);
        if (x > max_chain) {
            max_chain = x;
            max_num = i;
        }
    }
    printf("Solution: %d\n", max_num);

    end_time();
}
