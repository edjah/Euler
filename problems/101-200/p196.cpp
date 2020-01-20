#include "lib/utility.hh"
#include <atomic>

std::vector<long> prime_neighbors(long n, long level) {
    std::vector<long> neighbors;

    long lvl_start = level * (level - 1) / 2 + 1;
    long lvl_end = level * (level + 1) / 2;

    neighbors.push_back(n + level);         // directly below
    neighbors.push_back(n + level + 1);     // lower right

    if (n > lvl_start) {
       neighbors.push_back(n - level);      // upper left
       neighbors.push_back(n + level - 1);  // lower left
    }
    if (n < lvl_end) {
        neighbors.push_back(n - level + 1); // directly above
    }
    if (n < lvl_end - 1) {
        neighbors.push_back(n - level + 2); // upper right
    }

    std::vector<long> results;
    for (long neighbor : neighbors) {
        if (miller_rabin(neighbor)) {
            results.push_back(neighbor);
        }
    }
    return results;
}

long S(long level) {
    long lvl_start = level * (level - 1) / 2 + 1;
    long lvl_end = level * (level + 1) / 2;

    std::atomic<long> answer = 0;

    #pragma omp parallel for
    for (long n1 = lvl_start; n1 <= lvl_end; ++n1) {
        if (miller_rabin(n1)) {
            auto immediate_neighbors = prime_neighbors(n1, level);
            if (immediate_neighbors.size() >= 2) {
                answer += n1;
            } else {
                for (long n2 : prime_neighbors(n1, level)) {
                    bool flag = false;
                    int n2_lvl = n2 > n1 ? level + 1 : level - 1;
                    for (long n3 : prime_neighbors(n2, n2_lvl)) {
                        if (n1 != n3) {
                            flag = true;
                        }
                    }

                    if (flag) {
                        answer += n1;
                        break;
                    }
                }
            }
        }
    }

    return answer;
}

int main(void) {
    start_time();
    printf("Solution: %li\n", S(5678027) + S(7208785));
    end_time();
}
