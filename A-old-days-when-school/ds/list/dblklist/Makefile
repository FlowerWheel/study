CC = gcc
CFLAGS = -I../libc -ggdb -Wall
VPATH = ../libc

.PHONY: all clean

all : main

main : main.o dblklist.o error.o
	${CC} ${CFLAGS} -o $@ $^

clean:
	-rm *.o
