CC = gcc
CFLAGS = -Wall -ggdb

.PHONY : all clean clean-all

EXE = main 
all : ${EXE}

main : main.o dlist.o
	${CC} ${CFLAGS} -o $@ $^

clean :
	-rm *.o

clean-all :
	-rm *.o ${EXE}
