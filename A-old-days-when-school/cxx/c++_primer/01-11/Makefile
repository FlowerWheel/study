all : plus helloworld comment  \
	const test array

plus : plus.cpp
	g++ $^ -o $@ 

helloworld : helloworld.cpp
	g++ $^ -o $@

comment : comment.cpp
	g++ $^ -o $@

#const : const.cpp
#	g++ $^ -o $@

const : const.cpp
	g++ $^ -o $@

test : test.cpp
	g++ $^ -o $@

array : array.o
	g++ $^ -o $@
