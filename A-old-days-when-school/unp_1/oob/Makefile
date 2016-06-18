
CC = gcc
CFLAGS = -I../lib -Wall -g
LIBS = 
VPATH = ../lib/

all : tcpsendoob01 tcprecvoob01 tcpsendoob02 tcprecvoob02 \
	tcpsendoob03 tcprecvoob03  tcpsendoob04 tcprecvoob04  

DEP_tcpsendoob01 = $(patsubst %c, %o, $(wildcard ../lib/*.c))
tcpsendoob01 : tcpsendoob01.o $(DEP_tcpsendoob01)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

DEP_tcprecvoob01 = $(patsubst %c, %o, $(wildcard ../lib/*.c))
tcprecvoob01 : tcprecvoob01.o $(DEP_tcprecvoob01)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

DEP_tcpsendoob02 = $(patsubst %c, %o, $(wildcard ../lib/*.c))
tcpsendoob02 : tcpsendoob02.o $(DEP_tcpsendoob02)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

DEP_tcprecvoob02 = $(patsubst %c, %o, $(wildcard ../lib/*.c))
tcprecvoob02 : tcprecvoob02.o $(DEP_tcprecvoob02)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

DEP_tcpsendoob03 = $(patsubst %c, %o, $(wildcard ../lib/*.c))
tcpsendoob03 : tcpsendoob03.o $(DEP_tcpsendoob03)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

DEP_tcprecvoob03 = $(patsubst %c, %o, $(wildcard ../lib/*.c))
tcprecvoob03 : tcprecvoob03.o $(DEP_tcprecvoob03)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

DEP_tcpsendoob04 = $(patsubst %c, %o, $(wildcard ../lib/*.c))
tcpsendoob04 : tcpsendoob04.o $(DEP_tcpsendoob04)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

DEP_tcprecvoob04 = $(patsubst %c, %o, $(wildcard ../lib/*.c))
tcprecvoob04 : tcprecvoob04.o $(DEP_tcprecvoob04)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


clean :
	-rm *.o
