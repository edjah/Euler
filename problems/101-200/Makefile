%: %.c
	gcc -std=c11 -O3 $< -o $@ -lm -Wall -fopenmp

%: %.cpp
	g++ -std=c++17 -O3 $< -o $@ -lm -lmpfr -lgmp -Wall -fopenmp -ggdb
