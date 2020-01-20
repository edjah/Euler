#include "lib/utility.hh"

using namespace std;

int simulation_trial(unsigned int seed) {
    vector<pair<int, int>> possible_jumps = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

    vector<pair<int, int>> flea_positions;
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            flea_positions.push_back({i, j});
        }
    }


    for (int ring = 0; ring < 50; ++ring) {
        for (size_t p = 0; p < flea_positions.size(); ++p) {
            vector<pair<int, int>> options;

            auto [i, j] = flea_positions[p];
            for (auto [di, dj] : possible_jumps) {
                if (i + di >= 0 && i + di < 30 && j + dj >= 0 && j + dj < 30) {
                    options.push_back({i + di, j + dj});
                }
            }

            flea_positions[p] = options[rand_r(&seed) % options.size()];
        }
    }


    int grid[30][30] = {};
    for (auto [i, j] : flea_positions) {
        grid[i][j] += 1;
    }

    int num_empty = 0;
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            num_empty += (grid[i][j] == 0);
        }
    }

    return num_empty;
}

double simulate(int num_trials) {
    double tot = 0;

    #pragma omp parallel for
    for (int i = 0; i < num_trials; ++i) {
        int trial_res = simulation_trial(rand());

        #pragma omp critical
        tot += trial_res;
    }

    return tot / num_trials;
}


double exact_count() {
    constexpr int max_count = 15;
    using Distribution = array<double, max_count + 1>;

    // initializing the distribution for each cell
    vector<vector<Distribution>> dists;
    for (int i = 0; i < 30; ++i) {
        dists.push_back({});
        for (int j = 0; j < 30; ++j) {
            Distribution d = {0.0, 1.0};
            dists[i].push_back(d);
        }
    }

    // helper function to get the indices of neighboring cells
    auto get_neighbors = [](int i, int j) {
        static vector<pair<int, int>> dirs = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

        vector<pair<int, int>> res;
        for (auto [di, dj] : dirs) {
            if (i + di >= 0 && i + di < 30 && j + dj >= 0 && j + dj < 30) {
                res.push_back({i, j});
            }
        }
        return res;
    };

    // pre-compute the binomial distribution PMF for different parameters
    vector<vector<Distribution>> binomial_dist;
    for (int n = 0; n <= max_count; ++n) {
        binomial_dist.push_back(vector<Distribution>(5));

        for (int num_neighbors = 2; num_neighbors <= 4; ++num_neighbors) {
            double p = 1.0 / num_neighbors;
            double log_nCk = 0;

            for (int k = 0; k <= n; ++k) {
                if (k > 0) {
                    log_nCk += log(n - k + 1) - log(k);
                }
                double log_pmf = log_nCk + k*log(p) + (n - k)*log(1 - p);
                binomial_dist[n][num_neighbors][k] = exp(log_pmf);
            }
        }
    }

    function<Distribution(vector<Distribution>&)> get_next_dist = [&](vector<Distribution>& dists) {
        Distribution res = {};

        assert(dists.size() == 2 || dists.size() == 3 || dists.size() == 4);

        // TODO: get rid of this hardcoded trash :(
        if (dists.size() == 2) {
            for (size_t n = 0; n <= max_count; ++n)
                for (size_t a = 0; a <= n; ++a)
                    res[n] += dists[0][a] * dists[1][n - a];
        }

        if (dists.size() == 3) {
            for (size_t n = 0; n <= max_count; ++n)
                for (size_t a = 0; a <= n; ++a)
                    for (size_t b = 0; b <= n - a; ++b)
                        res[n] += dists[0][a] * dists[1][b] * dists[2][n - a - b];
        }

        if (dists.size() == 4) {
            for (size_t n = 0; n <= max_count; ++n)
                for (size_t a = 0; a <= n; ++a)
                    for (size_t b = 0; b <= n - a; ++b)
                        for (size_t c = 0; c <= n - a - b; ++c)
                            res[n] += dists[0][a] * dists[1][b] * dists[2][c] * dists[3][n - a - b - c];
        }

        return res;
    };

    // figuring out how the distributions change with each ring
    for (int ring = 0; ring < 50; ++ring) {
        // fprintf(stderr, "finished ring: %d\n", ring);

        vector<vector<Distribution>> updated_dists = dists;

        for (int i = 0; i < 30; ++i) {
            for (int j = 0; j < 30; ++j) {

                vector<Distribution> neighbor_dists;
                for (auto [ni, nj] : get_neighbors(i, j)) {
                    int p = get_neighbors(ni, nj).size();

                    // TODO: don't think this math is correct :(
                    Distribution n_dist = {};
                    for (int n1 = 0; n1 <= max_count; ++n1) {
                        for (int n2 = 0; n2 <= max_count; ++n2) {
                            n_dist[n2] += dists[i][j][n1] * binomial_dist[n1][p][n2];
                        }
                    }

                    double tot = vector_sum<double>(n_dist);
                    for (int a = 0; a <= max_count; ++a) {
                        n_dist[a] /= tot;
                    }

                    neighbor_dists.push_back(n_dist);
                }

                updated_dists[i][j] = get_next_dist(neighbor_dists);
            }
        }

        dists = updated_dists;
    }

    // adding up P(cell = 0) for each cell
    double expected_empty = 0;
    for (int i = 0; i < 30; ++i) {
        for (int j = 0; j < 30; ++j) {
            expected_empty += dists[i][j][0];
        }
    }

    return expected_empty;
}

int main() {
    start_time();

    // Exact result: 331.091497
    // // Simulation result: 330.874337
    printf("Simulation result: %.6f\n", simulate(10000));
    printf("Solution: %.6f\n", exact_count());
    end_time();
}
