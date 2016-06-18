SHELL = /bin/sh
VPATH = ../lib/
LIBS = 
CFLAGS = -I../lib -g -Wall
CC = gcc

all : unixbind \
	unixstrsrv01 unixstrcli01 \
	unixdgsrv01 unixdgcli01 \

		
unixbind : unixbind.o error.o warpsock.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

unixstrsrv01 : unixstrsrv01.o error.o warpsock.o sig_chld.o str_echo.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

unixstrcli01 : unixstrcli01.o error.o warpsock.o str_cli.o warpsysio.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

unixdgsrv01 : unixdgsrv01.o error.o warpsock.o dg_echo.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

unixdgcli01 : unixdgcli01.o error.o warpsock.o dg_cli.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)


.PHONY : clean

clean :
	rm *.o
