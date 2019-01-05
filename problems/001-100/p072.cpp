#include "lib/utility.hh"

int main(void) {
    start_time();

    std::vector<int> phi = totient_table(1000000);
    long total = std::accumulate(phi.begin() + 2, phi.end(), 0L);
    printf("Solution: %li\n", total);

    end_time();
}
