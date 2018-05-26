#include <iostream>
#include <vector>
#include "lib/utility.h"
#define N 10000000

int main(void) {
    start_time();

    std::vector<int> a(N + 1, 0);
    long steps = 0;
    for (int i = 1; i <= N; i++) {
        for (int j = i; j <= N; j += i) {
            a[j] += 1;
            steps += 1;
        }
    }

    int tot = 0;
    for (int i = 1; i < N; i++) {
        tot += a[i] == a[i + 1];
    }

    printf("Solution: %d\n", tot);

    end_time();
}
