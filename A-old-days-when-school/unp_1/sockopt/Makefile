SHELL 	= /bin/sh
VPATH 	= ../lib/
CC 		= gcc
CFLAGS 	= -I../lib -Wall -g
LIBS 	= 

.PHONY : all clean clean-all

all : checkopts

checkopts : checkopts.o ../lib/warpsock.o ../lib/error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

clean : 
	-rm *.o

clean-all :
	-rm *.o  checkopts
