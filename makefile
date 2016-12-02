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

problem.o: state.o
	$(CC) $(CFLAGS) $(INCL) -c src/problem.cpp -o build/problem.o

state.o:
	$(CC) $(CFLAGS) $(INCL) -c src/state.cpp -o build/state.o

bbsolver_test: bbsolver.o
	$(CC) $(CFLAGS) $(INCL) -o bin/bbsolver_test test/bbsolver_test.cpp build/bbsolver.o

bbsolver.o:
	$(CC) $(CFLAGS) $(INCL) -c src/bbsolver.cpp -o build/bbsolver.o

heuristic_test: state.o manhattandist.o graph.o heuristic.o bbsolver.o problem.o
	$(CC) $(CFLAGS) $(INCL) -o bin/heuristic_test test/heuristic_test.cpp build/bbsolver.o build/state.o build/problem.o build/manhattandist.o build/graph.o build/heuristic.o

graph.o: state.o
	$(CC) $(CFLAGS) $(INCL) -c src/graph.cpp -o build/graph.o

manhattandist.o: state.o graph.o
	$(CC) $(CFLAGS) $(INCL) -c src/manhattandist.cpp -o build/manhattandist.o

heuristic.o: state.o bbsolver.o graph.o manhattandist.o
	$(CC) $(CFLAGS) $(INCL) -c src/heuristic.cpp -o build/heuristic.o

ida_star_test: ida_star.o state.o problem.o manhattandist.o graph.o heuristic.o bbsolver.o
	$(CC) $(CFLAGS) $(INCL) -o bin/ida_star_test test/ida_star_test.cpp build/ida_star.o build/state.o build/problem.o build/manhattandist.o build/graph.o build/heuristic.o build/bbsolver.o

ida_star.o: heuristic.o
	$(CC) $(CFLAGS) $(INCL) -c src/ida_star.cpp -o build/ida_star.o

bfs_test: bfs.o state.o problem.o
	$(CC) $(CFLAGS) $(INCL) -o bin/bfs_test test/bfs_test.cpp build/bfs.o build/state.o build/problem.o

bfs.o:
	$(CC) $(CFLAGS) $(INCL) -c src/bfs.cpp -o build/bfs.o

deadlock.o:
	$(CC) $(CFLAGS) $(INCL) -c src/deadlock.cpp -o build/deadlock.o

deadlock_test: state.o problem.o deadlock.o
	$(CC) $(CFLAGS) $(INCL) -o bin/deadlock_test test/deadlock_test.cpp build/deadlock.o build/problem.o build/state.o

clean:
	rm -f bin/* build/*
