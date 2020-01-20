#include "lib/utility.hh"

using namespace std;

constexpr int limit = 10000;
constexpr int mod = 1000000007;

vector<pair<int, int>> allowable_steps;
vector<vector<int>> cache;

int count(int i, int j) {
    if (i == 0 && j == 0) {
        return 1;
    } else if (i < 0 || j < 0) {
        return 0;
    } else if (j > i) {
        return count(j, i);
    }

    int& cache_v = cache[i][j];
    if (cache_v != -1) {
        return cache_v;
    }

    int ans = 0;
    for (auto [x, y] : allowable_steps) {
        ans = (ans + count(i - x, j - y)) % mod;
    }

    cache_v = ans;
    return ans;

}

int main() {
    start_time();

    // getting a list of fibonacci numbers
    unordered_set<int> fibonacci_numbers;
    int tmp = 0, prev = 0, curr = 1;
    while (curr <= 2 * limit) {
        fibonacci_numbers.insert(curr);
        tmp = curr;
        curr = curr + prev;
        prev = tmp;
    }

    // get a list of allowable step sizes
    for (int x = 0; x <= limit; ++x) {
        for (int y = 0; y <= limit; ++y) {
            int dist = round(sqrt(x*x + y*y));
            if (dist*dist == x*x + y*y && fibonacci_numbers.count(dist)) {
                allowable_steps.push_back({x, y});
            }
        }
    }

    cache = vector(limit + 1, vector<int>(limit + 1, -1));
    printf("Solution: %d\n", count(limit, limit));

    end_time();
}
