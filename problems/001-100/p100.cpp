#include "lib/utility.hh"


int main(void) {
    start_time();

    /*
    b * (b - 1) / (t * (t - 1)) = 1 / 2 => t(t - 1) - 2b(b - 1) == 0
    This can be turned into a Diophantine equation and solved.

    But, I just ran this in Mathematica:
    Reduce[0 < b < 10^12 < t && t (t - 1) - 2 b (b - 1) == 0, {b, t}, Integers]
        b == 756872327473 && t == 1070379110497
    */
    printf("Solution: %li\n", 756872327473);

    end_time();
}

