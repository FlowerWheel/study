#include ../Makefile
SHELL = /bin/sh

.SUFFIXES:
.SUFFIXES:.c .o .h
CC = gcc
CFLAGS = -I../libc -Wall -g
LDFLAGS =
LIBS = -lpthread
VPATH = 

all : clean printFileType access travedir


#DEP = $(patsubst %.c, %.o *.c $(wildcard *.c))

printFileType : printFileType.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

#access : access.c $(patsubst %.c, %.o,  $(wildcard ../libc/*.c))
#	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) $(LDFLAGS)


access : access.c $(patsubst %.c, %.o,  $(wildcard ../libc/error.c))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)


travedir : travedir.o $(patsubst %.c, %.o, $(wildcard ../libc/*.o))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)


.PHONY : clean

clean :
	-rm *.o
