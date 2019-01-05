#define DESIRED_PRECION 128
#include "bignum.h"
#define MAGIC_PRIME 32117
#define NUM_OPS 1000000



// 3.3 ms overhead (from volatile assignment)
void benchmark_long_parsing() {
    // volatile bignum* x;
    for (long i = -NUM_OPS / 2; i < NUM_OPS / 2; i++) {
        bignum_free(bignum_from_long(MAGIC_PRIME * i));
    }
}


// 0 ms overhead
void benchmark_string_parsing() {
    char* a = "-812732189301259872132801938217365123021143218752189320129381";
    for (long i = 0; i < NUM_OPS; i++) {
        bignum_free(bignum_from_string(a));
    }
}

// 0.3 ms overhead (from volatile assignment)
void benchmark_to_long() {
    char* a = "-812732189301259872132801938217365123021143218752189320129381";
    bignum* b = bignum_from_string(a);
    volatile long x;
    for (int i = 0; i < NUM_OPS; i++) {
        x = bignum_to_long(b);
    }
    bignum_free(b);
}

// 0 ms overhead
void benchmark_to_string() {
    char* a = "-812732189301259872132801938217365123021143218752189320129381";
    bignum* b = bignum_from_string(a);
    for (int i = 0; i < NUM_OPS; i++) {
        free(bignum_to_string(b));
    }
    bignum_free(b);
}

// 0.3 ms overhead
void benchmark_compare() {
    char* s = "-812732189301259872132801938217365123021143218752189320129381";
    bignum* b = bignum_from_string(s);

    volatile int x = 0;
    for (int i = 0; i < NUM_OPS; i++) {
        x = bignum_compare(b, b);
    }
    bignum_free(b);
}

void benchmark_add() {
    char* s = "812732189301259872132801938217365123021143218752189320129381";
    bignum* b = bignum_from_string(s);

    bignum* x = bignum_from_long(0);
    bignum* tmp;
    for (int i = 0; i < NUM_OPS; i++) {
        tmp = bignum_add(x, b);
        bignum_free(x);
        x = tmp;
    }
    bignum_free(x);
    bignum_free(b);
}

void benchmark_subtract() {
    char* s = "812732189301259872132801938217365123021143218752189320129381";
    bignum* b = bignum_from_string(s);

    bignum* x = bignum_from_long(0);
    bignum* tmp;
    for (int i = 0; i < NUM_OPS; i++) {
        tmp = bignum_sub(x, b);
        bignum_free(x);
        x = tmp;
    }
    bignum_free(x);
}


void benchmark_mult() {
    // char* s1 = "812732189301259872132801938217365123021143218752189320129381812732189301259872132801938217365123021143218752189320129381812732189301259872132801938217365123021143218752189320129381812732189301259872132801938217365123021143218752189320129381812732189301259872132801938217365123021143218752189320129381812732189301259872132801938217365123021143218752189320129381812732189301259872132801938217365123021143218752189320129381812732189301259872132801938217365123021143218752189320129381";
    // char* s2 = "812732189301259872132801938217365123021143218752189320129382812732189301259872132801938217365123021143218752189320129382812732189301259872132801938217365123021143218752189320129382812732189301259872132801938217365123021143218752189320129382812732189301259872132801938217365123021143218752189320129382812732189301259872132801938217365123021143218752189320129382812732189301259872132801938217365123021143218752189320129382812732189301259872132801938217365123021143218752189320129382";
    char* s1 = "812732189301259872132801938217365123021143218752189320129381";
    char* s2 = "812732189301259872132801938217365123021143218752189320129382";

    bignum* a = bignum_from_string(s1);
    bignum* b = bignum_from_string(s2);

    bignum* result = bignum_from_long(0);
    for (int i = 0; i < NUM_OPS; i++) {
        bignum_free(bignum_mult(a, b));
    }

    bignum_free(a);
    bignum_free(b);
}

void benchmark_div() {
    char* s1 = "812732189301259872132801938217365123021143218752189320129381";
    char* s2 = "17181273218930125987210193821736512302114321875218931";
    bignum* a = bignum_from_string(s1);
    bignum* b = bignum_from_string(s2);
    for (int i = 0; i < NUM_OPS; i++) {
        bignum_free(bignum_div(a, b));
    }
    bignum_free(b);
}

void benchmark_mod_exp() {
    char* s = "812732189301259872132801938217365123021143218752189320129381";
    bignum* b = bignum_from_string(s);

    for (int i = 0; i < NUM_OPS; i++) {
        bignum_free(bignum_mod_exp(b, b, b));
    }
    bignum_free(b);

}

int main(void) {
    double start, end;

    start = tstamp();
    benchmark_long_parsing();
    end = tstamp();
    fprintf(stderr, "Long parsing:      %.3f ms\n", 1000.0 * (end - start));

    start = tstamp();
    benchmark_to_long();
    end = tstamp();
    fprintf(stderr, "To long:           %.3f ms\n", 1000.0 * (end - start));

    start = tstamp();
    benchmark_string_parsing();
    end = tstamp();
    fprintf(stderr, "String parsing:    %.3f ms\n", 1000.0 * (end - start));

    start = tstamp();
    benchmark_to_string();
    end = tstamp();
    fprintf(stderr, "To string:         %.3f ms\n", 1000.0 * (end - start));

    start = tstamp();
    benchmark_compare();
    end = tstamp();
    fprintf(stderr, "\nComparison:        %.3f ms\n\n", 1000.0 * (end - start));

    start = tstamp();
    benchmark_add();
    end = tstamp();
    fprintf(stderr, "Addition:          %.3f ms\n", 1000.0 * (end - start));

    start = tstamp();
    benchmark_subtract();
    end = tstamp();
    fprintf(stderr, "Subtraction:       %.3f ms\n", 1000.0 * (end - start));

    start = tstamp();
    benchmark_mult();
    end = tstamp();
    fprintf(stderr, "Multiplication:    %.3f ms\n", 1000.0 * (end - start));

    start = tstamp();
    benchmark_div();
    end = tstamp();
    fprintf(stderr, "Divison:           %.3f ms\n", 1000.0 * (end - start));

    start = tstamp();
    benchmark_mod_exp();
    end = tstamp();
    fprintf(stderr, "Exponentiation:    %.3f ms\n", 1000.0 * (end - start));
}
