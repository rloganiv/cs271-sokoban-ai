# Compiler
CC = g++

# Flags
CFLAGS = -std=c++11

# Directories
BIN = bin/
SRC = src/
INCL = -Iinclude/

# Make commands
problem_test: state.o problem.o
	$(CC) $(CFLAGS) $(INCL) -o bin/problem_test test/problem_test.cpp build/problem.o build/state.o
state_test: state.o
	$(CC) $(CFLAGS) $(INCL) -o bin/state_test test/state_test.cpp build/state.o

problem.o: state.o
	$(CC) $(CFLAGS) $(INCL) -c src/problem.cpp -o build/problem.o

state.o:
	$(CC) $(CFLAGS) $(INCL) -c src/state.cpp -o build/state.o

clean:
	rm -f bin/* build/*
