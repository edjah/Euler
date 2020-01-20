#include "lib/utility.h"

#define limit 10000
#define modulus 50515093L

int main() {
    start_time();

    int* S = malloc(sizeof(int) * limit);
    S[0] = 290797;
    for (int i = 1; i < limit; ++i) {
        long r = S[i];
        S[i] = (r * r) % modulus;
    }

    int* left = malloc(sizeof(int) * limit);
    int* right = malloc(sizeof(int) * limit);

    left[0] = 0;
    for (int i = 0; i < limit; ++i) {

    }

    end_time();
}
