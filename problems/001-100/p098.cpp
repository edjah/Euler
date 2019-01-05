#include "lib/utility.hh"

std::unordered_map<std::string, std::vector<std::string>> anagrams;

void increasing_sequences(std::vector<std::vector<int>>& sequences,
                          std::vector<int>& curr, size_t max_size, size_t start,
                          int limit) {
    if (curr.size() == max_size) {
        sequences.push_back(curr);
        return;
    }

    for (size_t i = start; i <= limit - (max_size - curr.size()); ++i) {
        curr.push_back(i);
        increasing_sequences(sequences, curr, max_size, i + 1, limit);
        curr.pop_back();
    }
}

std::vector<std::vector<int>> increasing_sequences(int count, int limit) {
    std::vector<std::vector<int>> sequences;
    std::vector<int> curr;
    increasing_sequences(sequences, curr, count, 0, limit);
    return sequences;
}

int try_square_anagram(const std::string& a, const std::string& b) {
    if (a.size() > 10) {
        return 0;
    }

    int best = 0;

    std::unordered_set<char> uniq_chars_set(a.begin(), a.end());
    std::vector<int> uniq_chars(uniq_chars_set.begin(), uniq_chars_set.end());

    std::unordered_map<char, int> mapping;
    std::string x = a;
    std::string y = b;

    for (std::vector<int>& seq : increasing_sequences(uniq_chars.size(), 10)) {
        for (auto& perm : permutations<int>(seq)) {
            for (size_t i = 0; i < perm.size(); ++i) {
                mapping[uniq_chars[i]] = '0' + perm[i];
            }

            for (size_t i = 0; i < x.size(); ++i) {
                x[i] = mapping[a[i]];
                y[i] = mapping[b[i]];
            }
            int xi = std::stoi(x);
            int yi = std::stoi(y);
            if (x[0] != '0' && y[0] != '0' && is_square(xi) && is_square(yi)) {
                best = std::max(best, std::max(xi, yi));
            }
        }
    }

    return best;
}


int main(void) {
    start_time();

    // reading data and pre-processing it
    const char* filename = "files/p098_words.txt";
    std::ifstream ifs(filename);
    if (!ifs.good()) {
        fprintf(stderr, "unable to open %s\n", filename);
        return 1;
    }

    std::string line;
    ifs >> line;
    line = replace(line, "\"", "");
    std::vector<std::string> vocabulary = split(line, ",");

    // listing out all of the anagrams
    for (std::string& s : vocabulary) {
        std::string copy = s;
        std::sort(copy.begin(), copy.end());
        anagrams[copy].push_back(s);
    }

    // iterating through all pairs of anagrams
    int best_square = 0;
    for (const auto& [_, v] : anagrams) {
        if (v.size() > 1) {
            for (size_t i = 0; i < v.size(); ++i) {
                for (size_t j = i + 1; j < v.size(); ++j) {
                    int square = try_square_anagram(v[i], v[j]);
                    best_square = std::max(best_square, square);
                }
            }
        }
    }

    printf("Solution: %d\n", best_square);

    end_time();
}

