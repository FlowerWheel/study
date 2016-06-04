SHELL = /bin/sh

CC = gcc
CFLAGS = -I../lib -Wall -g
LIBS = 
VPATH = ../lib/

all : dgsrv dgcli


DEP_dgsrv = $(patsubst %.c, %.o, $(wildcard ../lib/*.c))
dgsrv : dgsrv.o $(DEP_dgsrv)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

DEP_dgcli = $(patsubst %.c, %.o, $(wildcard ../lib/*.c))
dgcli : dgcli.o dgclibcast.o $(DEP_dgcli)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


clean : 
	-rm *.o
