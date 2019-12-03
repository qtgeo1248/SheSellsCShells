ifeq ($(DEBUG), true)
	CC = gcc -g
else
	CC = gcc
endif

all: main.o shells.o
	gcc -o program main.o shells.o

main.o: main.c shells.h
	gcc -c main.c

shells.o: shells.c shells.h
	gcc -c shells.c

run:
	./program

clean:
	rm *.o

memcheck:
	valgrind --leak-check=yes ./program
