#include "lib/utility.hh"

constexpr int limit = 1000001;

int divisor_sum[limit];

void populate_divisor_sum_table() {
    for (int i = 1; i < limit; i++) {
        for (int j = 2 * i; j < limit; j += i) {
            divisor_sum[j] += i;
        }
    }
}

int chain_length(int i) {
    std::unordered_set<int> seen;
    int start = i;
    int answer;
    while (1) {
        if (i >= limit) {
            answer = -1;
            break;
        } else if (seen.count(i)) {
            answer = (i == start) ? seen.size() : -1;
            break;
        }
        seen.insert(i);
        i = divisor_sum[i];
    }

    return answer;
}

int main(void) {
    start_time();

    populate_divisor_sum_table();

    int longest_chain_length = 0;
    int longest_chain_start = 0;
    for (int i = 1; i < limit; ++i) {
        int length = chain_length(i);
        if (length > longest_chain_length) {
            longest_chain_length = length;
            longest_chain_start = i;
        }
    }
    printf("Solution: %d | %d\n", longest_chain_start, longest_chain_length);

    end_time();
}

