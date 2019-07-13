#include "lib/utility.h"

#define TRI_HEIGHT 1000

long subtri_cache[TRI_HEIGHT][TRI_HEIGHT];
long tri[TRI_HEIGHT][TRI_HEIGHT];


void fill_triangle() {
    int t = 0;
    for (int i = 0; i < TRI_HEIGHT; ++i) {
        for (int j = 0; j <= i; ++j) {
            t = (615949*t + 797807) % (1 << 20);
            tri[i][j] = t - (1 << 19);
        }
    }
}


long minimum_subtriangle_sum() {
    long ans = 0;
    for (int j = 0; j < TRI_HEIGHT; ++j) {
        for (int i = TRI_HEIGHT - 1; i >= j; --i) {
            long diag = tri[i][j];
            subtri_cache[i][0] = tri[i][j];

            for (int n = 0; n < TRI_HEIGHT - i - 1; ++n) {
                diag += tri[i + n + 1][j + n + 1];
                subtri_cache[i][n + 1] = subtri_cache[i + 1][n] + diag;
                ans = MIN(ans, subtri_cache[i][n + 1]);
            }
        }
    }
    return ans;
}

int main() {
    start_time();
    fill_triangle();
    printf("Solution: %li\n", minimum_subtriangle_sum());
    end_time();
}
