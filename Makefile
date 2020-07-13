CC = gcc

cpy: main.o
	gcc -o cpy main.o

main.o:
	gcc -c -o main.o main.c

clean:
	rm *.o cpy


