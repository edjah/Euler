all: test

test: test.c
    gcc -std=c11 -Ofast -lm test.c primes.h -o test
