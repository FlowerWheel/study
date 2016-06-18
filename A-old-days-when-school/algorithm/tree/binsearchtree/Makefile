CC = gcc
CFLAGS = -Wall -ggdb -I../bintree
SRC_DIR = ../bintree
VPATH = ../bintree

.PHONY : all clean clean-all

EXE = main 
OBJ = 

all : ${EXE} ${OBJ}

main : main.o binsearchtree.o bintree.o stack.o queue.o list.o
	${CC} ${CFLAGS} -o $@ $^
	
clean :
	-rm *.o

clean-all :
	-rm *.o ${EXE}
