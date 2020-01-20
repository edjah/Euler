#include "lib/utility.hh"

using namespace std;

vector<pair<string, int>> guesses = {
    {"5616185650518293", 2},
    {"3847439647293047", 1},
    {"5855462940810587", 3},
    {"9742855507068353", 3},
    {"4296849643607543", 3},
    {"3174248439465858", 1},
    {"4513559094146117", 2},
    {"7890971548908067", 3},
    {"8157356344118483", 1},
    {"2615250744386899", 2},
    {"8690095851526254", 3},
    {"6375711915077050", 1},
    {"6913859173121360", 1},
    {"6442889055042768", 2},
    {"2321386104303845", 0},
    {"2326509471271448", 2},
    {"5251583379644322", 2},
    {"1748270476758276", 3},
    {"4895722652190306", 1},
    {"3041631117224635", 3},
    {"1841236454324589", 3},
    {"2659862637316867", 2}
};

constexpr int NUM_CHARS = 16;

using possiblity = array<int, NUM_CHARS>;

string possibility_to_string(possiblity& p, bool gap = false) {
    string s;
    for (int i = 0; i < NUM_CHARS; ++i) {
        for (int d = 0; d < 10; ++d) {
            if (p[i] & (1 << d)) {
                s += to_string(d);
            }
        }

        if (i != NUM_CHARS - 1 && gap) {
            s += " ";
        }
    }
    return s;
}


possiblity minimal_complete_possibility;

void build_minimal_complete_possibility_set() {
    for (int digit = 0; digit < NUM_CHARS; ++digit) {
        int possible = 0;
        for (auto& [guess, _] : guesses) {
            possible |= 1 << (guess[digit] - '0');
        }

        // special case where if exactly 1 item is missing, then
        // it's possible that missing item is the answer
        if (__builtin_popcount(possible) == 9) {
            int missing = ((1 << 10) - 1) ^ possible;
            fprintf(stderr, "special casing for digit %d | missing %d\n",
                    digit, __builtin_ffs(missing) - 1);
            possible = (1 << 10) - 1;
        }

        minimal_complete_possibility[digit] = possible;
    }
}


vector<possiblity> make_possibility_set(string guess, int num_correct) {
    if (num_correct == 0) {
        possiblity p = minimal_complete_possibility;
        for (int i = 0; i < NUM_CHARS; ++i) {
            p[i] &= ~(1 << (guess[i] - '0'));
        }
        return { p };
    }

    vector<possiblity> possibility_set;
    for (auto& combo : combinations<int>(arange(NUM_CHARS), num_correct)) {
        possiblity p = minimal_complete_possibility;
        for (int i = 0; i < NUM_CHARS; ++i) {
            if (std::count(combo.begin(), combo.end(), i)) {
                p[i] = 1 << (guess[i] - '0');
            } else {
                p[i] &= ~(1 << (guess[i] - '0'));
            }
        }
        possibility_set.push_back(p);
    }

    return possibility_set;
}


bool dfs(const vector<vector<possiblity>>& possibility_sets, possiblity& p, size_t guess_no) {
    if (guess_no == guesses.size()) {
        // verify that the possibility set is a singleton for each digit
        for (int i : p) {
            if (__builtin_popcount(i) != 1) {
                fprintf(stderr, "false positive: %s\n",
                        possibility_to_string(p, true).c_str());
                return false;
            }
        }
        return true;
    }


    for (auto q : possibility_sets[guess_no]) {
        bool flag = true;
        possiblity new_p = p;

        for (int i = 0; i < NUM_CHARS; ++i) {
            new_p[i] = p[i] & q[i];
            if (new_p[i] == 0) {
                flag = false;
            }
        }

        if (flag && dfs(possibility_sets, new_p, guess_no + 1)) {
            p = new_p;
            return true;
        }
    }

    return false;
}


int main() {
    start_time();

    build_minimal_complete_possibility_set();

    std::sort(guesses.begin(), guesses.end(), [](auto& a, auto& b) {
        return a.second < b.second;
    });

    vector<vector<possiblity>> possibility_sets;
    for (auto& [guess, num_correct] : guesses) {
        possibility_sets.push_back(make_possibility_set(guess, num_correct));
    }

    possiblity p = minimal_complete_possibility;
    if (!dfs(possibility_sets, p, 0)) {
        fprintf(stderr, "failed to find a solution\n");
    } else {
        printf("Solution: %s\n", possibility_to_string(p).c_str());
    }

    end_time();
}
