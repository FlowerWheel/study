CC = gcc
CFLAGS = -I../libc
VPATH = ../libc

CCFLAGS = `mysql_config --cflags`
LIBFLAGS = `mysql_config --libs`


test : test.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(CCFLAGS) $(LIBFLAGS) 
