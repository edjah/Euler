#include "lib/utility.h"

#define NUM_FRACTIONS 14

int program[NUM_FRACTIONS][2] = {
    {17, 91}, {78, 85}, {19, 51}, {23, 38}, {29, 33},
    {77, 29}, {95, 23}, {77, 19}, {1, 17},
    {11, 13}, {13, 11}, {15, 2}, {1, 7}, {55, 1}
};

int prime_factors[100][4] = {
    [2] = {2},
    [7] = {7},
    [11] = {11},
    [13] = {13},
    [15] = {3, 5},
    [17] = {17},
    [19] = {19},
    [23] = {23},
    [29] = {29},
    [33] = {3, 11},
    [38] = {2, 19},
    [51] = {3, 17},
    [55] = {5, 11},
    [77] = {7, 11},
    [78] = {2, 3, 13},
    [85] = {5, 17},
    [91] = {7, 13},
    [95] = {5, 19}
};


void fractran(int limit) {
    int counts[30] = {[2] = 1};

    for (int i = 1; i <= limit; ++i) {
        for (int f = 0; f < NUM_FRACTIONS; ++f) {
            int num = program[f][0];
            int den = program[f][1];

            bool is_divisible = true;
            int z = 0;

            // checking if the current number is divisible by the denominator
            // uses the fact that all the numbers in the program are squarefree
            while (prime_factors[den][z]) {
                if (!counts[prime_factors[den][z]]) {
                    is_divisible = false;
                    break;
                }
                z += 1;
            }

            if (!is_divisible) {
                continue;
            }

            // dividing by the denominator
            z = 0;
            while (prime_factors[den][z]) {
                counts[prime_factors[den][z]] -= 1;
                z += 1;
            }

            // multiplying by the numerator
            z = 0;
            while (prime_factors[num][z]) {
                counts[prime_factors[num][z]] += 1;
                z += 1;
            }
            break;
        }

        // check if the current number is a power of 2
        if (!(counts[3] || counts[5] || counts[7] || counts[11] || counts[13]
              || counts[17] || counts[19] || counts[23] || counts[29])) {
            fprintf(stderr, "power of 2 at iteration: %d | %d\n", i, counts[2]);
        }
    }
}

int main() {
    // 104743
    fractran(1000000000);
}


