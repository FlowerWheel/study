SHELL = /bin/sh

CC = gcc
CFLAGS = -I../lib -Wall -g
LIBS = 

all : printinfo prmac


DEP_PRIINFO = $(patsubst %c, %o, $(wildcard ../lib/*.c))
printinfo : printinfo.o get_ifi_info.o $(DEP_PRIINFO)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

DEP_PRMAC = $(patsubst %c, %o, $(wildcard ../lib/*.c))
prmac : prmac.o get_ifi_info.o $(DEP_PRMAC)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
