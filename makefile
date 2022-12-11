all: jc

jc: Deque.o token.o jc.o
	gcc -g -Wall -std=c11 -o jc Deque.o token.o jc.o

Deque.o: Deque.c Deque.h
	gcc -g -Wall -std=c11 -c Deque.c

token.o: token.c token.h Deque.h
	gcc -g -Wall -std=c11 -c token.c

jc.o: jc.c token.h Deque.h
	gcc -g -Wall -std=c11 -c jc.c

clean:
	rm -f *.o jc