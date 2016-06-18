CC = g++
CFLAGS = -ggdb -Wall -std=c++11

all : vector set string


vector : vector.cpp
	$(CC) $(CFLAGS) -o $@  $^

set : set.cpp
	$(CC) $(CFLAGS) -o $@  $^

string : string.cpp
	$(CC) $(CFLAGS) -o $@  $^


.PHONY : clean

clean : 
	-rm *.o
