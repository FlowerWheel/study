SHELL = /bin/sh
.SUFFIXES:
.SUFFIXES:.c .o
srcdir =
CC = gcc
CFLAGS = -I../lib -Wall -g
CCFLAGS =
LDFLAGS = 
VPATH = ../lib
LIBS = 

EXE = udpsrv_01 udpcli_01\
	udpsrv_02 udpcli_02\
	udpsrv_03 udpcli_03\
	udpsrv_04 udpcli_04\
	udpsrv_05 udpcli_05\
	udpsrv_06 udpcli_06\
	udpsrvselect01\

.PHONY : all clean clean-all


all : ${EXE}

DEP = $(wildcard ../lib/*.c)

udpcli_01 : $(DEP) udpcli_01.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpsrv_01 : $(DEP) udpsrv_01.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpcli_02 : $(DEP) udpcli_02.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpsrv_02 : $(DEP) udpsrv_02.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpcli_03 : $(DEP) udpcli_03.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpsrv_03 : $(DEP) udpsrv_03.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpcli_04 : $(DEP) udpcli_04.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpsrv_04 : $(DEP) udpsrv_04.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpcli_05 : $(DEP) udpcli_05.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpsrv_05 : $(DEP) udpsrv_05.o 
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpcli_06 : $(DEP) udpcli_06.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpsrv_06 : $(DEP) udpsrv_06.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

udpsrvselect01 : $(DEP) udpsrvselect01.o
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
check:
installcheck:
installdirs:


clean:
	-rm *.o

clean-all :
	-rm *.o ${EXE}
