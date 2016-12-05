#a Compiler
CC = g++

# Flags
CFLAGS = -std=c++11 -g

# Directories
BIN = bin/
SRC = src/
INCL = -Iinclude/

# Make commands
problem_test: state.o problem.o deadlock.o
	$(CC) $(CFLAGS) $(INCL) -o bin/problem_test test/problem_test.cpp build/problem.o build/state.o build/deadlock.o

state_test: state.o
	$(CC) $(CFLAGS) $(INCL) -o bin/state_test test/state_test.cpp build/state.o

problem.o:
	$(CC) $(CFLAGS) $(INCL) -c src/problem.cpp -o build/problem.o

state.o:
	$(CC) $(CFLAGS) $(INCL) -c src/state.cpp -o build/state.o

bbsolver_test: bbsolver.o
	$(CC) $(CFLAGS) $(INCL) -o bin/bbsolver_test test/bbsolver_test.cpp build/bbsolver.o

bbsolver.o:
	$(CC) $(CFLAGS) $(INCL) -c src/bbsolver.cpp -o build/bbsolver.o

heuristic_test: state.o manhattandist.o graph.o heuristic.o bbsolver.o problem.o
	 $(CC) $(CFLAGS) $(INCL) -o bin/heuristic_test test/heuristic_test.cpp build/bbsolver.o build/state.o build/problem.o build/manhattandist.o build/graph.o build/heuristic.o build/deadlock.o

graph.o:
	$(CC) $(CFLAGS) $(INCL) -c src/graph.cpp -o build/graph.o

simplemanhattan_test: state.o simplemanhattandist.o manhattandist.o graph.o heuristic.o bbsolver.o problem.o
	 $(CC) $(CFLAGS) $(INCL) -o bin/simplemanhattan_test test/simplemanhattan_test.cpp build/bbsolver.o build/state.o build/problem.o build/simplemanhattandist.o build/manhattandist.o build/graph.o build/heuristic.o build/deadlock.o


simplemanhattandist.o:
	$(CC) $(CFLAGS) $(INCL) -c src/simplemanhattandist.cpp -o build/simplemanhattandist.o

manhattandist.o:
	$(CC) $(CFLAGS) $(INCL) -c src/manhattandist.cpp -o build/manhattandist.o

heuristic.o:
	$(CC) $(CFLAGS) $(INCL) -c src/heuristic.cpp -o build/heuristic.o

ida_star_test: ida_star.o state.o problem.o manhattandist.o graph.o heuristic.o bbsolver.o deadlock.o parameters.o
	$(CC) $(CFLAGS) $(INCL) -o bin/ida_star_test test/ida_star_test.cpp build/ida_star.o build/state.o build/problem.o build/manhattandist.o build/graph.o build/heuristic.o build/bbsolver.o build/deadlock.o build/parameters.o

ida_star.o:
	$(CC) $(CFLAGS) $(INCL) -c src/ida_star.cpp -o build/ida_star.o

a_star_test: a_star.o state.o problem.o manhattandist.o graph.o heuristic.o bbsolver.o deadlock.o parameters.o
	$(CC) $(CFLAGS) $(INCL) -o bin/a_star_test test/a_star_test.cpp build/a_star.o build/state.o build/problem.o build/manhattandist.o build/graph.o build/heuristic.o build/bbsolver.o build/deadlock.o build/parameters.o

a_star.o:
	$(CC) $(CFLAGS) $(INCL) -c src/a_star.cpp -o build/a_star.o


bfs_test: bfs.o state.o problem.o deadlock.o parameters.o
	$(CC) $(CFLAGS) $(INCL) -o bin/bfs_test test/bfs_test.cpp build/bfs.o build/state.o build/problem.o build/deadlock.o build/parameters.o

bfs.o:
	$(CC) $(CFLAGS) $(INCL) -c src/bfs.cpp -o build/bfs.o

deadlock.o:
	$(CC) $(CFLAGS) $(INCL) -c src/deadlock.cpp -o build/deadlock.o

deadlock_test: state.o problem.o deadlock.o
	$(CC) $(CFLAGS) $(INCL) -o bin/deadlock_test test/deadlock_test.cpp build/deadlock.o build/problem.o build/state.o

parameters.o:
	$(CC) $(CFLAGS) $(INCL) -c src/parameters.cpp -o build/parameters.o

clean:
	rm -f bin/* build/*
