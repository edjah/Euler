#include "lib/utility.hh"


bool integral_area(long a, long b) {
    if (b % 2 == 0) {
        long squared_height = a * a -  (b / 2) * (b / 2);
        return is_square(squared_height);
    }

    // if a == b + 1 then squared_height == 3/4b^2 + 2b + 1
    // if a == b - 1 then squared_height == 3/4b^2 - 2b + 1
    // in both cases, if b is odd, then it is impossible for the result to be
    // an integer, which means that is impossible for it to be square
    return false;
}

int main(void) {
    start_time();

    long total_perim = 0;
    long side_length = 3;

    while (3 * side_length - 1 < 1000000000) {
        if (integral_area(side_length, side_length + 1)) {
            total_perim += 3 * side_length + 1;
        }
        if (integral_area(side_length, side_length - 1)) {
            total_perim += 3 * side_length - 1;
        }
        side_length += 1;
    }
    printf("Solution: %zu\n", total_perim);

    end_time();
}

