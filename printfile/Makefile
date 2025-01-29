CC=gcc
CCOPTS=-Wall -Wextra
LIBS=

SRCS=$(wildcard *.c)
TARGETS=$(SRCS:.c=)

.PHONY: all clean

all: $(TARGETS)

clean:
	rm -f $(TARGETS)
	rm -f output.txt

%: %.c
	$(CC) $(CCOPTS) -o $@ $< $(LIBS)
    
