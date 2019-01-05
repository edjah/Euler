#include "lib/utility.hh"


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

int min_path_sum_2(unsigned r, unsigned c) {
    if (r == matrix.size() - 1 && c == matrix[0].size() - 1) {
        return matrix[r][c];
    }

    long cache_key = long(r) << 32 | c;
    if (cache[cache_key]) {
        return cache[cache_key];
    }

    int a = (r < matrix.size() - 1) ? min_path_sum_2(r + 1, c) : INT_MAX;
    int b = (c < matrix[0].size() - 1) ? min_path_sum_2(r, c + 1) : INT_MAX;
    cache[cache_key] = matrix[r][c] + std::min(a, b);
    return cache[cache_key];
}

int main(void) {
    start_time();
    load_matrix("files/p081_matrix.txt");
    printf("Solution: %d\n", min_path_sum_2(0, 0));
    end_time();
}
