%: %.c
	gcc -std=c11 -O3 $< -o $@ -lm -ggdb -Wall -lgmp

%: %.cpp
	g++ -std=c++17 -O3 $< -o $@ -lm -ggdb -Wall -lgmp -fopenmp

big_cpp: bignum.hh bignum_test.cpp
	g++ -std=c++17 -O3 bignum_test.cpp -o big_cpp -Wall -ggdb -lgmp
