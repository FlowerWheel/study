#file start

SOURCES = $(wildcard *.c)
OBJS := $(patsubst %.c, %.o,  $(SOURCES))

all: main

%.d: %.c
	@set -e; rm -f $@; /
	$(CC) -MM  $< > $@.$$$$; /
	sed 's, /($*/)/.o[ :]*, /1.o $@ : , g' < $@.$$$$ > $@; /
	rm -f $@.$$$$

sinclude $(SOURCES:.c=.d)

main:$(OBJS)
	$(CC) -o main $(OBJS)

clean:
	rm -f *.o test *.d
	#file end
