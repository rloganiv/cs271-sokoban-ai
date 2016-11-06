# Compiler
CC = g++

# Flags
CFLAGS = -std=c++11 -g

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

ida_star_test: ida_star.o state.o problem.o
	$(CC) $(CFLAGS) $(INCL) -o bin/ida_star_test test/ida_star_test.cpp build/ida_star.o build/state.o build/problem.o

ida_star.o:
	$(CC) $(CFLAGS) $(INCL) -c src/ida_star.cpp -o build/ida_star.o

clean:
	rm -f bin/* build/*
