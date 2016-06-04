CC = gcc
CFLAGS = -I../libc -g -Wall
VPATH = ../libc
LIB = -lm


.PHONY :all clean print

all : main

main : main.o sort.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)


clean : 
	-rm *.o

print : *.c
	lpr -p $?
