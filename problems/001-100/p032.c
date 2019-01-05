#include "lib/utility.h"


int used[9] = {};

void reset_used() {
    for (int i = 0; i < 9; i++) {
        used[i] = 0;
    }
}

bool test_uniq(int a) {
    while (a > 0) {
        int d = a % 10;
        if (d == 0 || used[d - 1]) {
            return false;
        }
        used[d - 1] = 1;
        a /= 10;
    }
    return true;
}

int num_length(unsigned x) {
    if (x == 0) {
        return 1;
    }

    int size = 0;
    while (x > 0) {
        size += 1;
        x /= 10;
    }
    return size;
}

int main(void) {
    start_time();

    int sols[100];
    int sols_size = 0;
    int tot = 0;

    for (int a = 1; a < 100000; a++) {
        reset_used();
        if (!test_uniq(a)) {
            continue;
        }

        for (int b = a + 1; b < 100000; b++) {
            int len = num_length(a) + num_length(b) + num_length(a * b);
            if (len < 9) {
                continue;
            } else if (len > 9) {
                break;
            }

            reset_used();
            if (test_uniq(a) && test_uniq(b) && test_uniq(a * b)) {
                bool uniq_solution = true;
                for (int i = 0; i < sols_size; i++) {
                    if (sols[i] == a * b) {
                        uniq_solution = false;
                        break;
                    }
                }
                if (uniq_solution) {
                    sols[sols_size++] = a * b;
                    tot += a * b;
                }
            }
        }
    }

    printf("Solution: %d\n", tot);

    end_time();
}
