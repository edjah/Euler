#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    clock_t start = clock();

    int c = 1, x = 3;
    while ((double) c/x >= 1.0 / 12345.0) {
        if ((x & (x - 1)) == 0) {
            c++;
        }
        x++;
    }
    printf("Solution: %lu\n", (long) x * (x + 1));

    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);
}
