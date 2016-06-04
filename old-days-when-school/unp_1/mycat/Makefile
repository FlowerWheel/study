SHELL = /bin/sh
.SUFFIXES : .c .h .cpp .sh .o .i

CC = gcc
CFLAGS = -I../lib -Wall -g
CCFLAGS = 
LDFLAGS =
LIBS = 
VPATH = ../lib

all : mycat openfile \


MCDEP = $(patsubst %.c, %.o, $(wildcard ../lib/*.c))
mycat : $(MCDEP) mycat.o read_fd.o my_open.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

OFDEP = $(patsubst %.c , %.o, $(wildcard ../lib/*.c))
openfile : $(OFDEP) openfile.o write_fd.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


#.PHONY : all install 
