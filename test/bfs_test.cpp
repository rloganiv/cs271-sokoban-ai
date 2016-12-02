#include "problem.h"
#include "state_space.h"
#include <iostream>
#include <vector>
#include "bfs.h"
#include <ctime>
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char** argv) {
    using namespace std;
   // Problem test_problem;
   // BBSolver solver;
    State *init_state;
    cout << "Initializing problem from file" << endl;
    Problem test_problem(argv[1]); // Solves

    init_state = test_problem.get_init_state();
    cout << "Printing initial state" << endl;
    init_state->print();

    cout << "Checking if initial state is a goal" << endl;
    cout << test_problem.goal_test(init_state) << endl;

    cout << "Calling BFS" << endl;
    std::vector<Action> path_to_goal;
    time_t start, end, diff;
    bfs b;
    auto t1 = Clock::now();
    path_to_goal = b.bfs_begin(*init_state, test_problem);
    auto t2 = Clock::now();
    cout << "Returned from BFS " << endl;
    std::cout << "Running time = "
              << std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count()
              << " nanoseconds" << std::endl;
    if(path_to_goal.empty())
    {
	cout << " No solution found " << endl;
	return -1;
    }
    else
    {
	cout << "Number of moves to the goal = " <<path_to_goal.size()<< endl;
    	cout << "Path to goal = ";

	// Print the path to the goal state
    	for(auto it = path_to_goal.begin(); it!= path_to_goal.end(); ++it)
		cout <<  *it << " ";
 	cout << endl;
    }
    return 0;
}

