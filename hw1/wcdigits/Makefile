all:   wcdigits

wcdigits: wcdigits.o
	gcc -o wcdigits wcdigits.o

wcdigits.o: wcdigits.c
	gcc -c wcdigits.c

clean:
	rm -f wcdigits.o
