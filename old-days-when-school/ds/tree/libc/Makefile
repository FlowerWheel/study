SHELL = /bin/sh
#.SUFFIXES:
#.SUFFIXES:.c .o
srcdir = 
CC = gcc
CFLAGS =  -Wall -g
CCFLAGS = 
LDFLAGS = 
VPATH = 
LIBS = -lpthread -lm

all : hello

DEP = $(patsubst %.c, %.o, hello.c $(wildcard *.c))
hello : $(DEP)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)




.PHONY : clean

clean : 
	rm *.o
