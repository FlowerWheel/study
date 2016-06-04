CC = gcc
CFLAGS = -Wall -ggdb 
SRC = 
VPATH = 

EXE = main
OBJ = 

.PHONY : all clean clean-all

all : ${EXE}

main : main.o strmatch.o
	${CC} ${CFLAGS} -o $@ $^


clean :
	-rm *.o

clean-all :
	-rm *.o ${EXE}
