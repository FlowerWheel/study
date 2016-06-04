SHELL = /bin/sh
#.SUFFIXES:
#.SUFFIXES:.c .o
srcdir = 
CC = gcc
CFLAGS =  -Wall -g -c
CCFLAGS = 
LDFLAGS = 
VPATH = 
LIBS = 

sources	:= ${wildcard *.c}
objects := ${patsubst %.c, %.o, ${source}}
#targets := ${basename ${sources}}

.PHONY : all clean clean-all

all : ${objects}

clean : 
	-rm -f ${objects} *.core

clean-all :
	-rm -f ${objects} ${targets} *.core

