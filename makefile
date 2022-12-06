all: jc

jc: jc.c token.o token.h Deque.o Deque.h
	gcc -g -Wall -std=c11 -o jc jc.c token.o Deque.o

token.o: token.c token.h
	gcc -g -Wall -std=c11 -c token.c

deque.o: Deque.c Deque.h
	gcc -g -Wall -std=c11 -c Deque.c