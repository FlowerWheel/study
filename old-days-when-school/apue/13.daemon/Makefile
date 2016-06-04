SHELL  	=	/bin/bash

VPATH 	= 	../libc/
CC 		= 	gcc
CFLAGS 	= 	-g -Wall -I../libc/ 

sources = 	$(wildcard *.c )
objects = 	$(patsubst %.c, %.o, $(sources))
targets = 	$(basename ${sources})

.PHONY : all clean clean-all

all : $(targets) $(objects)


daemon : daemon.o ../libc/error.o
	$(CC) $(CFLAGS) $^ -o $@

sleep : sleep.o
	$(CC) $(CFLAGS) $^ -o $@

clean :
	-rm $(objects)

clean-all :
	-rm $(objects) $(targets)
