CC = gcc
CCFLAGS = -Wall -g

CXX = g++
CXXFLAGS = -Wall -g -std=c++11

INCLUDE = 
STDLIB = 

LIBS = 

OBJS = 
TEST = 

all : adjgraph 


adjgraph : adjgraph.o
	$(CXX) $(CXXFLAGS) -o $@ $^ 

adjgraph.o : adjgraph.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $^ 


.PHONY : clean

clean : 
	-rm *.o
