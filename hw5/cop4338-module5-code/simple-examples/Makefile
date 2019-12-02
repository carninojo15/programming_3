all:	helloworld passargs bank pi

helloworld:	helloworld.c
	gcc -Wall $< -o $@

passargs:	passargs.c
	gcc -Wall $< -o $@

bank:	bank.c
	gcc -Wall $< -o $@

pi:	pi.c
	gcc -Wall $< -o $@

clean:
	rm -f helloworld passargs bank pi *.o core *~
