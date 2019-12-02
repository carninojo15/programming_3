all:	typewriter

typewriter:	typewriter.o ringbuf.o
	gcc typewriter.o ringbuf.o -o typewriter -lpthread

ringbuf.o:	ringbuf.h ringbuf.c
	gcc -c -Wall ringbuf.c -o ringbuf.o

typewriter.o:	ringbuf.h typewriter.c
	gcc -c -Wall typewriter.c -o typewriter.o

clean:
	$(RM) typewriter *.o *~
