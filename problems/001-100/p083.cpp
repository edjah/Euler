#include "lib/utility.hh"
#include "lib/fast_hashmap.hh"
#include "lib/priority_queue.hh"

std::vector<std::vector<int>> matrix;
ska::flat_hash_map<long, long> cache;

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

int dijkstra() {
    ska::flat_hash_map<long, long> dist;
    ska::flat_hash_set<long> visited;
    priority_queue<long, long> queue;
    long width = matrix[0].size();
    long height = matrix.size();
    for (long r = 0; r < height; ++r) {
        for (long c = 0; c < width; ++c) {
            dist[r << 32 | c] = INT_MAX;
            queue.insert(r << 32 | c, INT_MAX);
        }
    }

    queue.update_key(0, matrix[0][0]);
    dist[0] = matrix[0][0];

    while (1) {
        auto [best_key, best_dist] = queue.pop_top();
        long best_r = best_key >> 32;
        long best_c = best_key & 0xFFFFFFFF;

        std::vector<std::pair<long, long>> neighbors;
        if (best_r < height - 1) {
            neighbors.push_back({best_r + 1, best_c});
        }
        if (best_r > 0) {
            neighbors.push_back({best_r - 1, best_c});
        }
        if (best_c < width - 1) {
            neighbors.push_back({best_r, best_c + 1});
        }
        if (best_c > 0) {
            neighbors.push_back({best_r, best_c - 1});
        }

        for (auto [rn, cn] : neighbors) {
            long key = rn << 32 | cn;
            if (!visited.count(key)) {
                dist[key] = std::min(dist[key], best_dist + matrix[rn][cn]);
                queue.update_key(key, dist[key]);
            }
        }
        visited.insert(best_r << 32 | best_c);
        if (best_r == height - 1 && best_c == width - 1) {
            return best_dist;
        }
    }
}

int main(void) {
    start_time();
    load_matrix("files/p083_matrix.txt");
    printf("Solution: %d\n", dijkstra());
    end_time();
}
