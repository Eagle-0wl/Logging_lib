LIB:=liblogging.so
CFLAGS:= -Wall -fpic -shared
SRC:=$(wildcard *.c)
OBJS:=$(SRC:.c=.o)

.PHONY: all clean

all: $(LIB)

$(LIB): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(LIB)
