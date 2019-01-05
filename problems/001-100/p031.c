#include "lib/utility.h"

int num_coins = 8;
int coins[8] = {1, 2, 5, 10, 20, 50, 100, 200};
int cache[201][8] = { [0 ... 200] = { [0 ... 7] = -1 } };

int count_ways(int x, int idx) {
    if (x < 0) {
        return 0;
    } else if (x == 0) {
        return 1;
    } else if (cache[x][idx] != -1) {
        return cache[x][idx];
    }

    int ways = 0;
    for (int i = idx; i < num_coins; i++) {
        ways += count_ways(x - coins[i], i);
    }
    cache[x][idx] = ways;
    return ways;
}

int main(void) {
    start_time();
    printf("Solution: %d\n", count_ways(200, 0));
    end_time();
}
