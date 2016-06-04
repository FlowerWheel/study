CC = gcc
CFLAGS = -Wall -ggdb -I../bintree -I../binsearchtree
SRC_DIR = ../bintree 
VPATH = ../bintree ../binsearchtree

CXX = g++

.PHONY : all clean clean-all

EXE = main avl
OBJ = 

all : ${EXE} ${OBJ}

main : main.o avltree.o binsearchtree.o bintree.o stack.o queue.o list.o
	${CC} ${CFLAGS} -o $@ $^

avl : avl.o
	${CXX} -o $@ $^
	

clean :
	-rm *.o

clean-all :
	-rm *.o ${EXE}
