#include <stdio.h>
#include <time.h>


int main(int argc, char *argv[]) {
    clock_t start = clock();


    clock_t end = clock();
    double time = (double) (end - start) / CLOCKS_PER_SEC;
    printf("%f seconds to run\n", time);
}
