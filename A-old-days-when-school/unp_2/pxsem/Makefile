CC = gcc
CFLAGS = -I../libc -Wall -g
LIBS = -pthread -lrt


all : clean semcreate semunlink semgetvalue semwait sempost
	
semcreate : semcreate.o $(patsubst %.c, %.o, $(wildcard ../libc/error.o ))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

semunlink : semunlink.o $(patsubst %.c, %.o, $(wildcard ../libc/error.o ))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

semgetvalue : semgetvalue.o $(patsubst %.c, %.o, $(wildcard ../libc/error.o ))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)
	
semwait : semwait.o $(patsubst %.c, %.o, $(wildcard ../libc/error.o ))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

sempost : sempost.o $(patsubst %.c, %.o, $(wildcard ../libc/error.o ))
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS)

.PHONY : clean 
clean : 
	-rm *.o
