all:	myfork myls myshell

myfork:	myfork.o
	gcc myfork.o -o myfork

myfork.o:	myfork.c
	gcc -c myfork.c -o myfork.o

myls:	myls.o
	gcc myls.o -o myls

myls.o:	myls.c
	gcc -c myls.c -o myls.o

myshell:	myshell.o
	gcc myshell.o -o myshell

myshell.o:	myshell.c
	gcc -c myshell.c -o myshell.o

clean:
	rm -f myfork myls myshell *.o core *~
