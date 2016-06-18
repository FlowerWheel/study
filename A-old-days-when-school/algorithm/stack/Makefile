CC = gcc
CFLAGS = -I../list/flist -Wall -ggdb
VPATH = ../list/flist

.PHONY : all clean clean-all

EXE = main 
all : ${EXE}

main : main.o stack.o list.o
	${CC} ${CFLAGS} -o $@ $^

clean :
	-rm *.o

clean-all :
	-rm *.o ${EXE}
