SHELL = /bin/sh

CC = gcc
CFLAGS = -I../lib -Wall -g
LIBS = 

DEP_GETRT = $(patsubst %.c, %.o, $(wildcard ../lib/*.c))
getrt : getrt.o get_rtaddrs.o sock_masktop.o $(DEP_GETRT)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS) 
