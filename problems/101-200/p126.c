/*
The number of cubes in layer n of an x by y by z cuboid where
x >= y >= z is given by (formula derived via guess and check)

an^2 + bn + c

where

a = 4
b = 4 * (x + y + z - 3)
c = 2 * (x - 1) * (y - 1) + 2 * (x + y - 2) * (z - 1) + 2
*/

#include "lib/utility.h"

#define LIMIT 20000

inline int layer_count(int x, int y, int z, int n) {
    int a = 4;
    int b = 4 * (x + y + z - 3);
    int c = 2 * (x - 1) * (y - 1) + 2 * (x + y - 2) * (z - 1) + 2;
    return a*n*n + b*n + c;
}

int counts[LIMIT];

void compute_counts() {
    for (int x = 1; layer_count(x, x, x, 1) < LIMIT; ++x) {
        for (int y = x; layer_count(x, y, y, 1) < LIMIT; ++y) {
            for (int z = y; layer_count(x, y, z, 1) < LIMIT; ++z) {
                for (int n = 1; layer_count(x, y, z, n) < LIMIT; ++n) {
                    counts[layer_count(x, y, z, n)] += 1;
                }
            }
        }
    }
}

int main() {
    start_time();
    compute_counts();
    for (int i = 0; i < LIMIT; ++i) {
        if (counts[i] == 1000) {
            printf("Solution: %d\n", i);
            break;
        }
    }
    end_time();
}
