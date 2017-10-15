#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[]) {
    clock_t start = clock();

    for (int s = 1; s < 40000; s++) {
        for (int c = 1; c < 5000; c++) {
            k
        }
    }

    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);
}
