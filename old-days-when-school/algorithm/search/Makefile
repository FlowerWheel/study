CC = gcc 
CFLAGS = -I../libc -Wall -ggdb
VPATH = ../libc

.PHONY : all clean

EXE = main

all : ${EXE}

main : main.o search.o error.o
	${CC} ${CFLAGS} -o $@ $^

clean :
	-rm *.o

clean-all:
	-rm *.o ${EXE}


