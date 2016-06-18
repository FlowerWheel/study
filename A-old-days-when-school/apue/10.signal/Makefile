CC = gcc
CFLAGS = -I../libc -g -Wall

VPATH = ../libc

all : catchSIGUSR sleep errmsg prsigmask sigmsg rtsig sigprocmask \
	signal sigjmp sigsuspend abort system

catchSIGUSR : error.o catchSIGUSR.o 
	${CC} ${CFLAGS} -o $@ $^

sleep : sleep.o error.o
	${CC} ${CFLAGS} -o $@ $^

errmsg : errmsg.o
	${CC} ${CFLAGS} -o $@ $^

prsigmask : prsigmask.o error.o
	${CC} ${CFLAGS} -o $@ $^

sigmsg : sigmsg.o
	${CC} ${CFLAGS} -o $@ $^

rtsig : rtsig.o
	${CC} ${CFLAGS} -o $@ $^

sigprocmask :sigprocmask.o error.o
	${CC} ${CFLAGS} -o $@ $^

signal : signal.o
	${CC} ${CFLAGS} -o $@ $^

sigjmp : sigjmp.o error.o
	${CC} ${CFLAGS} -o $@ $^

sigsuspend : sigsuspend.o error.o
	${CC} ${CFLAGS} -o $@ $^

abort : abort.o
	${CC} ${CFLAGS} -o $@ $^

system : system.o
	${CC} ${CFLAGS} -o $@ $^



.PHONY : clean

clean : 
	-rm *.o
