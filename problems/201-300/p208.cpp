#include "lib/utility.hh"

using namespace std;

constexpr double turn_angle = 2.0 * M_PI / 5.0;
constexpr double zero_tolerance = 1e-6;

tuple<double, double, double> next_position(double x, double y, double dir, bool clockwise) {
    double r = clockwise ? 1 : -1;
    double cx = x - r * sin(dir);
    double cy = y + r * cos(dir);

    x = cx + r * sin(turn_angle + dir);
    y = cy - r * cos(turn_angle + dir);
    dir = dir + r * turn_angle;

    if (dir > 2 * M_PI) {
        dir -= 2 * M_PI;
    }
    if (dir < -2 * M_PI) {
        dir += 2 * M_PI;
    }
    return {x, y, dir};
}

double rnd(double x) {
    return round(x * 10000) / 10000;
}

unordered_map<tuple<double, double, double, int>, long> cache;

long count_paths(double x, double y, double dir, int steps_remaining) {
    if (steps_remaining == 0) {
        return abs(x) < zero_tolerance && abs(y) < zero_tolerance;
    }

    // heuristic to prune some paths early
    if (abs(x) + abs(y) > 2 * steps_remaining) {
        return 0;
    }

    tuple cache_key = {rnd(x), rnd(y), rnd(dir), steps_remaining};
    if (cache.count(cache_key)) {
        return cache[cache_key];
    }

    long ans = 0;
    for (bool clockwise : {false, true}) {
        auto [nx, ny, nd] = next_position(x, y, dir, clockwise);
        ans += count_paths(nx, ny, nd, steps_remaining - 1);
    }

    cache[cache_key] = ans;
    return ans;
}

int main() {
    start_time();

    long ans = count_paths(0, 0, 0, 70);
    printf("Solution: %li\n", ans);

    end_time();
}
