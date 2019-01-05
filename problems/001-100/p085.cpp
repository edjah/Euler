#include "lib/utility.hh"

int count_rectangles(int width, int height) {
    // for (int a = 1; a <= width; ++a) {
    //     for (int b = 1; b <= height; ++b) {
    //         total += (width - a + 1) * (height - b + 1);
    //     }
    // }

    // the above can be optimized to a closed form sum
    return (width * (width + 1) / 2) * (height * (height + 1) / 2);
}

int find_closest_area(int target) {
    int best_w = 0;
    int best_h = 0;
    int closest_count = 0;

    for (int w = 1; w < 1000; ++w) {
        for (int h = 1; h < 1000; ++h) {
            int count = count_rectangles(w, h);
            if (abs(count - target) < abs(closest_count - target)) {
                closest_count = count;
                best_w = w;
                best_h = h;
            }
        }
    }
    return best_w * best_h;
}

int main(void) {
    start_time();
    printf("Solution: %d\n", find_closest_area(2000000));
    end_time();
}
