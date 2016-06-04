include ../Makefile

LIBS = -pthread -lpthread
CFLAGS = -I../libc -Wall -g

all : clean prodcons2 prodcons3 prodcons6


prodcons2 : prodcons2.o $(patsubst %.c, %.o, $(wildcard ../libc/*.c))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)


prodcons3 : prodcons3.o $(patsubst %.c, %.o, $(wildcard ../libc/*.c))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

prodcons6 : prodcons6.o $(patsubst %.c, %.o, $(wildcard ../libc/*.c))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)




.PHONY : clean

clean :
	-rm *.o
