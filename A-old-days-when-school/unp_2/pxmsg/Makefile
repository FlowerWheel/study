CC = gcc
CFLAGS = -Wall -g
LIBS = 


all : mqcreate1 mqunlink

mqcreate1 : mqcreate1.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) -lrt

mqunlink : mqunlink.c
	$(CC) $(CFLAGS) $^ -o $@ $(LIBS) -lrt
