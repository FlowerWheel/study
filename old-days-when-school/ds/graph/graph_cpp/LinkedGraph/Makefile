CXX = g++
LIBS = 
DEGUG = -g
INCLUDE = -I./
CXX_STD = -std=c++11
CXXFLAGS = ${INCLUDE} ${CXX_STD} ${DEGUG} ${LIBS}

all : graph 
	
graph : graph.o
	$(CXX) -o $@ $^ $(DEGUG)
#	g++ -o $@ $^

.PHONY : clean

clean : 
	-rm *.o

clean_all : 
