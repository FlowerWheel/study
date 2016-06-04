SHELL 	= /bin/sh
.SUFFIXES:
.SUFFIXES:.c .o
srcdir 	:=
CC 		= gcc
CFLAGS 	= -I../lib -Wall -g
CCFLAGS =
LDFLAGS = 
VPATH 	= ../lib
LIBS 	= 

EXE = tcpserv01 tcpcli01 \
      tcpserv02 tcpcli02 \
      tcpserv03 tcpcli03 \

.PHONY : all clean clean-all

DEP = $(patsubst %.c, %.o, $(wildcard ../lib/*.c))

all :${DEP}  ${EXE} 
	
tcpserv01 : $(DEP) tcpserv01.o	
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)	

tcpcli01 : $(DEP) tcpcli01.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)	

tcpserv02 : $(DEP) tcpserv02.o	
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)	

tcpcli02 : $(DEP) tcpcli02.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)	

tcpserv03 : $(DEP) tcpserv03.o	
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)	

tcpcli03 : $(DEP) tcpcli03.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)	



install:
uninstall:
install-strip:
distclean:
mostlyclearn:
maintainer-clean:
TAGS:
info:
dvi:
dist:
#check:
installcheck:
installdirs:

clean:
	-rm *.o

clean-all : 
	-rm *.o ${EXE}
