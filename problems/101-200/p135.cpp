#include <iostream>
#include <vector>
#include "lib/utility.h"
using namespace std;

#define N 1000000

vector<int> divisors[N + 1];

void populate_divisors(int n) {
    for (int i = 1; i <= n; i++) {
        for (int j = i; j <= n; j += i) {
            divisors[j].push_back(i);
        }
    }
}

int count_sols(int n) {
    int count = 0;

    for (int d : divisors[n]) {
        int c = n / d;
        int a = (d + c) / 4;

        int x = (5 * d + c) / 4;
        int y = x - a;
        int z = y - a;

        if (x > 2 * a && x*x - y*y - z*z == n) {
            count++;
        }
    }
    return count;
}

int main(void) {
    start_time();

    populate_divisors(N);
    int count = 0;
    for (int n = 1; n < N; n++) {
        count += count_sols(n) == 10;
    }
    cout << "Solution: " << count << endl;

    end_time();
}
