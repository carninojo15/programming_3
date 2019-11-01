all:   temperature

temperature: temperature.o
	gcc -o temperature temperature.o

temperature.o: temperature.c
	gcc -c temperature.c

clean:
	rm -f temperature temperature.o core *~
