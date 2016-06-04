SHELL 	= /bin/bash

CC 		= gcc
CFLAGS  = -g -Wall -I../libc
VPATH 	= ../libc

sources = $(wildcard *.c)
objects = $(patsubst %.c, %.o, $(sources))
targets = $(basename $(objects))

.PHONY : all clean clean-all

all : $(targets)
	@echo build targets
	@echo 

NoBlockWrite : NoBlockWrite.o fileflags.o error.o
	$(CC) $(CFLAGS) $^ -o $@

clean : 
	rm $(objects)

clean-all :
	rm $(objects) $(targets)
