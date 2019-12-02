all: combo

combo: combo.o
	gcc combo.o -o combo

combo.o: combo.c
	gcc -c combo.c -o combo.o

clean:
	rm -f combo *.o core *~