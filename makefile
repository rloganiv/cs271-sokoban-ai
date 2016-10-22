# Compiler
CC = g++

# Flags
CFLAGS = -std=c++11

# Directories
BIN = bin/
SRC = src/
INCL = -Iinclude/

# Make commands
board_test: board.o
	$(CC) $(CFLAGS) $(INCL) -o bin/board_test test/board_test.cpp build/board.o

board.o:
	$(CC) $(CLFAGS) $(INCL) -c src/board.cpp -o build/board.o

clean:
	rm -f bin/* build/*
