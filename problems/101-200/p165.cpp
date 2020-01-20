#include "lib/utility.hh"
#include "lib/fraction.hh"

using Point = std::pair<int, int>;
using Segment = std::pair<Point, Point>;
using Intersection = std::pair<Fraction, Fraction>;

std::vector<Segment> generate_segments(int n) {
    std::vector<int> rand;
    long s = 290797;
    for (int i = 0; i < 4 * n; ++i) {
        s = s*s % 50515093;
        rand.push_back(s % 500);
    }

    std::vector<Segment> result;
    for (int i = 0; i < 4 * n; i += 4) {
        result.push_back({{rand[i], rand[i + 1]}, {rand[i + 2], rand[i + 3]}});
    }

    return result;
}

std::vector<Intersection> compute_intersections(const Segment& s1, const Segment& s2) {
    auto [a1, b1] = s1.first;
    auto [a2, b2] = s1.second;
    auto [c1, d1] = s2.first;
    auto [c2, d2] = s2.second;

    // Parametrize each segment by t1 and t2. Then solve a system of two
    // equations to compute the t1 and t2 where an intersection would occur.
    int t1_num = b1*(-c1 + c2) - c2*d1 + a1*(d1 - d2) + c1*d2;
    int t1_den = -(b1 - b2)*(c1 - c2) + (a1 - a2)*(d1 - d2);

    int t2_num = (b1 - b2)*c1 + a1*(b2 - d1) + a2*(-b1 + d1);
    int t2_den = (b1 - b2)*(c1 - c2) - (a1 - a2)*(d1 - d2);

    // if either of the denominators is zero, the segments are parallel or
    // at least one of the segments has zero length
    if (t1_den == 0 || t2_den == 0) {
        return {};
    }

    Fraction t1 = Fraction(t1_num, t1_den);
    Fraction t2 = Fraction(t2_num, t2_den);

    // Check if the intersection point is outside of either segment and
    // check if it is on an endpoint for either segment
    if (t1 <= 0 || t1 >= 1 || t2 <= 0 || t2 >= 1) {
        return {};
    }

    Fraction x = (a2 - a1)*t1 + a1;
    Fraction y = (b2 - b1)*t1 + b1;
    return {std::pair(x, y)};
}

int main() {
    start_time();

    std::unordered_set<Intersection> intersections;
    std::vector<Segment> segments = generate_segments(5000);
    for (size_t i = 0; i < segments.size() - 1; ++i) {
        for (size_t j = i + 1; j < segments.size(); ++j) {
            for (auto& r : compute_intersections(segments[i], segments[j])) {
                intersections.insert(r);
            }
        }
    }

    printf("Solution: %zu\n", intersections.size());
    end_time();
}
