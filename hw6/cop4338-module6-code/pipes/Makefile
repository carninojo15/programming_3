all:	mypipe mysort echorevert

mypipe:	mypipe.o
	gcc mypipe.o -o mypipe

mypipe.o:	mypipe.c
	gcc -c mypipe.c -o mypipe.o

mysort:	mysort.o
	gcc mysort.o -o mysort

mysort.o:	mysort.c
	gcc -c mysort.c -o mysort.o

echorevert:	echorevert.o
	gcc echorevert.o -o echorevert

echorevert.o:	echorevert.c
	gcc -c echorevert.c -o echorevert.o

clean:
	rm -f mypipe mysort echorevert *.o core *~
