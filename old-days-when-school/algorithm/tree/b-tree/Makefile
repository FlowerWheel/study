CC = gcc
CFLAGS = -ggdb -Wall

EXE = main

.PHONY : all clean clean-all

all : ${EXE}

main : main.o b-tree.o
	${CC} ${CFLAGS} -o $@ $^

clean :
	-rm *.o

clean-all : 
	-rm *.o ${EXE}
