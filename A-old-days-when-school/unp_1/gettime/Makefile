SHELL = /bin/sh
VPATH = ../lib/
CC = gcc
CFLAGS = -I../lib/ -g -Wall
CCFLAGS = 
LIBS =

all : daytimetcpserv daytimetcpcli \
	daytimeudpserv daytimeudpcli \
		

daytimetcpserv : daytimetcpserv.o error.o warpsock.o gai_tcp.o warpsysio.c warpstdio.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

daytimetcpcli : daytimetcpcli.o error.o warpsock.o gai_tcp.o warpsysio.c warpstdio.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

daytimeudpserv : daytimeudpserv.o error.o warpsock.o gai_udp.o warpsysio.c warpstdio.c
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

daytimeudpcli : daytimeudpcli.o error.o warpsock.o gai_udp.o warpsysio.c warpstdio.c 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY : clean
clean :
	rm *.o
