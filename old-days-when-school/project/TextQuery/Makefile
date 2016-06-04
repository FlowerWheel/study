CXX = g++
CXXFLAGS = -g -Wall -std=c++98
STD = 

EXE = t_TextQuery t_Query
OBJ = 

.PHONY : all clean clean-all

all : ${EXE}

t_TextQuery : t_TextQuery.o
	${CXX} ${CXXFLAGS} -o $@ $^

t_Query : t_Query.o
	${CXX} ${CXXFLAGS} -o $@ $^


clean :
	-rm *.o

clean-all :
	-rm *.o
	-rm ${EXE}
