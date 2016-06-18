CC = gcc
CFLAGS = -Wall -ggdb 
SRC_DIR = 
VPATH = ${SRC_DIR}

.PHONY : all clean clean-all

EXE = main 

all : ${EXE} 

main : main.o sort.o search.o
	${CC} ${CFLAGS} -o $@ $^
	

clean :
	-rm *.o

clean-all :
	-rm *.o ${EXE}
