CC = gcc
CFLAGS = -ggdb -Wall

EXE = main

.PHONY : all clean clean-all

all : ${EXE}

main : main.o cstree.o
	${CC} ${CFLAGS} -o $@ $^

clean :
	-rm *.o

clean-all : 
	-rm *.o ${EXE}
