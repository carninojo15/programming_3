all:   shellsort

shellsort: shellsort.o
	gcc -o shellsort shellsort.o

shellsort.o: shellsort.c
	gcc -c shellsort.c

clean:
	rm -f shellsort shellsort.o core *~
