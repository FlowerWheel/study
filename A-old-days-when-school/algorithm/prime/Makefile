CC = gcc
CFLAGS = -I../libc -g -Wall
LIBS = -lm

VPATH = ../libc

all : prime
#	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

prime : prime.o error.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
.PHONY : clear
clear : 
	-rm *.o
