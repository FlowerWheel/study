CC = g++ 
#STD=-std=c++98
#STD=-std=c++03
STD=-std=c++11
DEBUG=-ggdb
#LINK_OPTION=-lm
LINK_OPTION=-lboost_regex
CFLAGS=$(STD) $(DEBUG) $(LINK_OPTION)

all : regex Sales_item Person Screen cscope  \
	Fibnacci clean

regex: regex.o
	$(CC) -o $@ $^ $(CFLAGS)

regex.o: regex.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

Sales_item : Sales_item.o
	$(CC) -o $@ $^ $(CFLAGS)

Sales_item.o : Sales_item.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

Person : Person.o
	$(CC) -o $@ $^ $(CFLAGS)

Person.o : Person.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

Screen : Screen.o
	$(CC) -o $@ $^ $(CFLAGS)

Screen.o : Screen.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

cscope : cscope.o
	$(CC) -o $@ $^ $(CFLAGS)

cscope.o : cscope.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

#Message : Message.o
#	$(CC) -o $@ $^ 

Fibnacci : Fibnacci.o
	$(CC) -o $@ $^ $(CFLAGS)

Fibnacci.o : Fibnacci.cpp
	$(CC) -c -o $@ $^ $(CFLAGS)

.PHONY : clean

clean_all :
	rm Sales_item Person Screen cscope Fibnacci
	rm *.o

clean :
	rm *.o

