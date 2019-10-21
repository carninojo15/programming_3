all:	helloworld

helloworld:	helloworld.o printhello.o
	gcc helloworld.o printhello.o -o helloworld

helloworld.o:	helloworld.c
	gcc -c helloworld.c -o helloworld.o

printhellow.o:	printhello.c printhello.h
	gcc -c printhello.c -o printhello.o

clean:
	rm -f helloworld *.o core *~
