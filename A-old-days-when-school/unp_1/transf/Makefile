SHELL = /bin/sh 
SRCDIR = 
CC = gcc
CFLAGS = -I../lib -Wall -g
CCFLAGS = 
LDFLAGS =
VPATH = ../lib
LIBS = 

all : gethostbyname gethostbyaddr \
	getservbyname getservbyport \
	daytimetcpcli daytimetcpsrv \
	daytimetcpcli01 \
	
	
	
gethostbyname : gethostbyname.o error.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)
	
gethostbyaddr : gethostbyaddr.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

getservbyname : getservbyname.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

getservbyport : getservbyport.o error.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

daytimetcpcli : daytimetcpcli.o error.o warpsock.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

daytimetcpcli01 : daytimetcpcli01.o error.o warpsock.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

daytimetcpsrv : daytimetcpsrv.o error.o warpsock.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

#getaddrinfo : getaddrinfo.o error.o warpsock.o
#	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

.PHONY : clean
clean: 
	-rm *.o
	-rm ../lib/*.o
