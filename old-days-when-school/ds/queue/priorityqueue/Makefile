CC = gcc
CFLAGS = -I../libc -g -Wall
LIB = 
VPATH = ../libc


all : binheap_main leftheap_main skewheap_main


binheap_main : binheap_main.o  error.o  binheap.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

leftheap_main : leftheap_main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

skewheap_main : skewheap_main.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)
.PHONY : clear

clear : 
	-rm *.o
