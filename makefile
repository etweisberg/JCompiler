all: jc

jc: jc.c jc.o token.o token.h Deque.o Deque.h
	gcc -g -Wall -std=c11 -o jc jc.o token.o Deque.o

jc.o: jc.c token.h Deque.h
	gcc -g -Wall -std=c11 -c jc.c

token.o: token.c token.h
	gcc -g -Wall -std=c11 -c token.c

Deque.o: Deque.c Deque.h
	gcc -g -Wall -std=c11 -c Deque.c

clean:
	rm -f *.o jc