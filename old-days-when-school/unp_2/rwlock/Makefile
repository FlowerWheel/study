CC = gcc
CFLAGS = -I../libc -Wall -g
LIB = -lpthread


SRC = $(patsubst %.c, %.o, $(wildcard ../libc/error.o ../libc/wrappthread.o))

all : clean 






.PHONY : clean

clean :
	-rm *.o
