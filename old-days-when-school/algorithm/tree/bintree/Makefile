CC = gcc
CFLAGS = -Wall -ggdb #-I../../list/ -I../../stack/ -I../../queue/
SRC_DIR = #../../list/ ../../stack ../../queue/
VPATH = ${SRC_DIR}

.PHONY : all clean clean-all

EXE = main 
OBJ = stack.o queue.o list.o

all : ${EXE} 
#${OBJ}

main : main.o bintree.o stack.o queue.o list.o
	${CC} ${CFLAGS} -o $@ $^
	

# stack.o : stack.c list.c
# 	${CC} ${CFLAGS} -o $@ $^

# queue.o : queue.c list.c
# 	${CC} ${CFLAGS} -o $@ $^

# list.o : list.c
#	${CC} ${CFLAGS} -o $@ $^

clean :
	-rm *.o

clean-all :
	-rm *.o ${EXE}
