SHELL 	:= bash

inc 	:= /usr/include/mysql/
lib 	:= /usr/lib/mysql/

VPATH 	:= ../libc

CC 		:=  gcc
CFLAGS 	:= -I${inc} -g -Wall -O
LDLIBS  := -L${lib} -lmysqlclient -lz -lm -lcrypt

#CFLAGS 	:= `mysql_config --cflags`
#LIBFLAGS	:= `mysql_config --libs`

#CXX 		:= g++
#CXXFLAGS	:= -I${inc}

#LDFLAGS 	:= -static

sources := ${wildcard *.c}
objects := ${patsubst %c, %o, ${sources}}
targets := ${basename ${sources}}

.PHONY : all clean clean-all

all : ${targets} ${objects}

clean : 
	-rm -f ${objects} *.core

clean-all :
	-rm -f ${targets} ${objects} *.core
