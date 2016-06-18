CC = gcc
CFLAGS = -Wall -ggdb 
SRC = 
VPATH = 

EXE = main
OBJ = 

.PHONY : all clean clean-all

all : ${EXE}

main : main.o random.o
	${CC} ${CFLAGS} -o $@ $^


clean :
	-rm *.o

clean-all :
	-rm *.o ${EXE}
