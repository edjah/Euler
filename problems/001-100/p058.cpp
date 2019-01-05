#include "lib/utility.hh"
#include "lib/bignum.hh"

std::vector<int> spiral(int side_length) {
    std::vector<int> results;
    if (side_length <= 1) {
        results.push_back(1);
    } else {
        int start = side_length * side_length;
        for (int i = 3; i >= 0; --i) {
            results.push_back(start - (side_length - 1) * i);
        }
    }
    return results;
}

int main(void) {
    start_time();

    int side_length = 1;
    int prime_count = 0;
    int total_count = 1;

    do {
        side_length += 2;
        for (int x : spiral(side_length)) {
            prime_count += Bignum(x).is_prime();
            total_count += 1;
        }
    } while (prime_count * 10 > total_count);

    printf("Solution: %d\n", side_length);
    end_time();
}
