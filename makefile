# Compiler
CC = g++

# Flags
CFLAGS = -std=c++11

# Directories
BIN = bin/
SRC = src/
INCL = -Iinclude/

# Make commands
state_test: state.o
	$(CC) $(CFLAGS) $(INCL) -o bin/state_test test/state_test.cpp build/state.o

state.o:
	$(CC) $(CFLAGS) $(INCL) -c src/state.cpp -o build/state.o

clean:
	rm -f bin/* build/*
