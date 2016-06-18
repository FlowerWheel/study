CC = gcc
CFLAGS = -I../libc -g -Wall


all : clean getpw getspw getgrp utsname time



getpw : getpw.o $(patsubst %.c, %.o,  $(wildcard ../libc/error.o))
	$(CC) $(CFLAGS) $^ -o $@

getspw : getspw.o $(patsubst %.c, %.o,  $(wildcard ../libc/error.o))
	$(CC) $(CFLAGS) $^ -o $@

getgrp : getgrp.o $(patsubst %.c, %.o,  $(wildcard ../libc/error.o))
	$(CC) $(CFLAGS) $^ -o $@

utsname : utsname.o $(patsubst %.c, %.o,  $(wildcard ../libc/error.o))
	$(CC) $(CFLAGS) $^ -o $@

time : time.o $(patsubst %.c, %.o,  $(wildcard ../libc/error.o))
	$(CC) $(CFLAGS) $^ -o $@


.PHONY : clean

clean :
	-rm *.o
