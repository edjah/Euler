#include <iostream>
#include "lib/utility.h"
using namespace std;

#define N 50000000

int sol_count[N];


int main(void) {
    start_time();

    for (long x = 0; x < 3 * N / 2; x++) {
        for (long a = x / 5 + 1; a <= x / 2; a++) {
            long n = (5 * a -  x) * (x - a);
            if (n >= N) {
                break;
            }

            long y = x - a;
            long z = y - a;

            if (n < N && x > 2 * a && x*x - y*y - z*z == n) {
                sol_count[n]++;
            }
        }
    }

    int count = 0;
    for (int n = 0; n < N; n++) {
        count += sol_count[n] == 1;
    }
    cout << "Solution: " << count << endl;

    end_time();
}
