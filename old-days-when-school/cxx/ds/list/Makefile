SHELL 	= /bin/bash 

CXX 	= g++
CXXFLAGS= -g -Wall -std=c++11

.PHONY : all clean clean-all

all : list

list : list.o
	$(CXX) $(CFLAGS) -o $@ $^


clean : 
	-rm list.o

clean-all :
	-rm list.o list
