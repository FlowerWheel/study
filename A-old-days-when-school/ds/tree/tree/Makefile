CC = gcc
CFLAGS = -I../libc -ggdb -Wall
VPATH = ../libc

.PHONY: all clean

all : tree

tree : tree.o
	${CC} ${CFLAGS} -o $@ $^

clean:
	-rm *.o
