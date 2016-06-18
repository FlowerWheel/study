CC = gcc
CFLAGS = -Wall -g
LIBS =  


all : pipe1 popen1 mkfifo1


pipe1 : pipe1.c
	$(CC) $(CFLAGS)  $^ -o $@ $(LIBS)

popen1 : popen1.c
	$(CC) $(CFLAGS)  $^ -o $@ $(LIBS)

mkfifo1 : mkfifo1.c
	$(CC) $(CFLAGS)  $^ -o $@ $(LIBS)
