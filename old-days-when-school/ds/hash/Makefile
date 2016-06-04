CC = gcc
CFLAGS = -I../libc/ -g -Wall
LIB =  -lm


all : hash_main

hash_main : hash_main.o hash.o ../libc/error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

.PHONY : clear

clear : 
	-rm *.o
