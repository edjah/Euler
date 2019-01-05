#include "lib/utility.hh"

bool makes_right_triangle(int x1, int y1, int x2, int y2) {
    int a_sq = x1*x1 + y1*y1;
    int b_sq = x2*x2 + y2*y2;
    int c_sq = (x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1);

    // ensure that c is the longest side
    if (a_sq > c_sq) {
        std::swap(a_sq, c_sq);
    }
    if (b_sq > c_sq) {
        std::swap(b_sq, c_sq);
    }

    return a_sq > 0 && b_sq > 0 && c_sq > 0 && a_sq + b_sq == c_sq;
}

int main(void) {
    start_time();

    // easy brute force
    int count = 0;
    for (int x1 = 0; x1 <= 50; ++x1) {
        for (int y1 = 0; y1 <= 50; ++y1) {
            for (int x2 = 0; x2 <= 50; ++x2) {
                for (int y2 = 0; y2 <= 50; ++y2) {
                    count += makes_right_triangle(x1, y1, x2, y2);
                }
            }
        }
    }

    // divide by 2 to account for double counting
    printf("Solution: %d\n", count / 2);

    end_time();
}
