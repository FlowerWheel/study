VPATH=../libc
CFLAGS=-I../libc -g -Wall

.PHONY : clean all
all : BintreeCpp AvltreeCpp	bintree_main binsearchtree_main avltree_main 

BintreeCpp : BintreeCpp.o
	g++ -o $@ $^

AvltreeCpp : AvltreeCpp.o
	g++ -o $@ $^

bintree_main : bintree_main.o bintree.o stack.o bintree.o queue.o error.o 
	g++ $(CFLAGS) -o $@ $^

binsearchtree_main : binsearchtree_main.o binsearchtree.o bintree.o stack.o queue.o error.o
	g++ $(CFLAGS) -o $@ $^

avltree_main : avltree_main.o avltree.o error.o
	g++ $(CFLAGS) -o $@ $^

clean :
	-rm *.o
