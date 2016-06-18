
CC 	= gcc
CFLAGS 	=
LIB 	= -luv

objects = async.o hello-libuv.o common.o

.PHONY	: all hello-libuv clean


${objects}: common.h

all: async hello-libuv

hello-libuv: hello-libuv.o
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

asyncDeps = async.o common.o
${asyncDeps}: common.h
async: ${asyncDeps}
	$(CC) $(CFLAGS) -o $@ $^ $(LIB)

clean:
	yes | rm *.o


