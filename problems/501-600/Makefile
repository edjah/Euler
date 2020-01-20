%: %.c
	gcc -std=c11 -O3 $< -o $@ -lm -ggdb -Wall -lgmp -lpthread

%: %.cpp
	g++ -std=c++17 -O3 $< -o $@ -lm -ggdb -Wall -lgmp -lpthread

%: %.cc
	g++ -std=c++17 -O3 $< -o $@ -lm -ggdb -Wall -lgmp -lpthread
