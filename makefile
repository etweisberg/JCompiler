all: jc

jc: token.o jc.o
	gcc -g -Wall -std=c11 -o jc token.o jc.o

token.o: token.c token.h
	gcc -g -Wall -std=c11 -c token.c

jc.o: jc.c token.h
	gcc -g -Wall -std=c11 -c jc.c

clean:
	rm -f *.o jc