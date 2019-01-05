#include "lib/utility.hh"

enum direction {
    NONE, UP, DOWN, RIGHT
};

std::vector<std::vector<int>> matrix;
std::unordered_map<long, int> cache;

void load_matrix(const char* filename) {
    std::ifstream ifs(filename);
    if (!ifs.good()) {
        throw std::runtime_error("Unable to open " + std::string(filename));
    }

    std::string line;
    while (ifs >> line) {
        std::vector<int> row;
        for (const std::string& s : split(line, ",")) {
            row.push_back(stoi(s));
        }
        matrix.push_back(row);
    }
}

int min_path_sum_3(unsigned r, unsigned c, direction last_dir) {
    long cache_key = long(last_dir) << 62 | long(r) << 32 | c;

    if (c == matrix[0].size() - 1) {
        return matrix[r][c];
    } else if (cache.count(cache_key)) {
        return cache[cache_key];
    }

    int result = INT_MAX;
    if (r < matrix.size() - 1 && last_dir != UP) {
        result = std::min(result, min_path_sum_3(r + 1, c, DOWN));
    }
    if (r > 0 && last_dir != DOWN) {
        result = std::min(result, min_path_sum_3(r - 1, c, UP));
    }
    if (c < matrix[0].size() - 1) {
        result = std::min(result, min_path_sum_3(r, c + 1, RIGHT));
    }
    cache[cache_key] = matrix[r][c] + result;
    return cache[cache_key];
}

int main(void) {
    start_time();
    load_matrix("files/p082_matrix.txt");
    int result = INT_MAX;
    for (size_t i = 0; i < matrix.size(); ++i) {
        result = std::min(result, min_path_sum_3(i, 0, NONE));
    }
    printf("Solution: %d\n", result);
    end_time();
}
