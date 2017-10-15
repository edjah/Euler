all:
	ls | grep "\.c" | sed "s/.c//g" | xargs make

%: %.c
	gcc -std=c11 -Ofast -lm $< -o $@ -lgmp

clean:
	ls | grep -v "\.\|makefile" | xargs rm -rf
