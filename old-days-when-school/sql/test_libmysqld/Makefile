
inc 	:= /usr/include/mysql/
lib 	:= /usr/lib/mysql/

CC 		:= gcc
CFLAGS 	:= -g -W -Wall
CXXFLAGS:= -I${inc} -D_THREAD_SAFE -D_REENTRANT
LDFLAGS := -static
LDLIBS 	= -L${lib} -lmysqld -lmysqlclient -lz -lm -lcrypt

ifneq (, $(shell grep FreeBSD /COPYRIGHT 2>/deb/null))
	#FreeBSD
	LDFLAGS += -pthread
else
	#Assume Linux
	LDLIBS += lpthread
endif

sources := ${wildcard *.c}
objects := ${patsubst %c, %o, ${sources}}
targets := ${basename ${sources}}

all : ${targets}

clean : 
	rm -f ${targets} ${objects} *.core
