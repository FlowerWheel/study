SHELL 	= /bin/bash 

.SUBFFIXES: .exe .cpp 

CC 		= g++
CPP  	= g++
CXXFLAGS= -g -Wall

.cpp.exe:
	$(CPP) $<


sources = $(wildcard *.cpp)
objects = $(patsubst %.cpp, %.o, $(sources))
targets = $(basename $(objects))

.PHONY : all clean clean-all

all : $(targets) $(objects)
# echo $(sources) 
# echo $(objects) 
# echo $(targets)

clean :
	-rm *.o *.core

clean-all :
	-rm *.o
	-rm $(EXE)
