#include "lib/utility.h"


unsigned long count_paths(int n) {
    unsigned long grid[n + 1][n + 1];
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            grid[i][j] = 0;
        }
    }

    for (int i = 0; i <= n; i++) {
        grid[i][n] = 1;
        grid[n][i] = 1;
    }

    for (int i = n - 1; i >= 0; i--) {
        for (int j = n - 1; j >= 0; j--) {
            grid[i][j] = grid[i][j + 1] + grid[i + 1][j];
        }
    }
    return grid[0][0];

}

int main(void) {
    start_time();
    printf("Solution: %lu\n", count_paths(20));
    end_time();
}
