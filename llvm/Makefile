.PHONY: all clean
CFLAGS=-g -Wall -Wextra
LDFLAGS=-lm
CC=g++

%.o: %.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

test: test.o llvm.o
	$(CC) -o $@ $^ $(CFLAGS) $(LDFLAGS)
	./test

clean:
	rm -rf llvm
	rm -rf *.o
	rm -rf test
