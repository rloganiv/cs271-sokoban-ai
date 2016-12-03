#include "problem.h"
#include "state_space.h"
#include "ida_star.h"
#include <iostream>
#include <vector>
#include "assignmentsolver.h"
#include "heuristic.h"
#include "bbsolver.h"
#include <chrono>

typedef std::chrono::high_resolution_clock Clock;

int main(int argc, char** argv) {
    using namespace std;
    Problem test_problem(argv[1]);
    cout << "Initializing problem from file" << endl;
    State *init_state;
    init_state = test_problem.get_init_state();
    BBSolver solver;

    cout << "Printing initial state" << endl;
    init_state->print();

    cout << "Checking if initial state is a goal" << endl;
    cout << test_problem.goal_test(init_state) << endl;

    cout << "Calling IDA*" << endl;
    std::vector<Action> path_to_goal;

    ida_star ida;
    auto t1 = Clock::now();
    path_to_goal = ida.ida_begin(*init_state, test_problem, solver);
    auto t2 = Clock::now();
    cout << "Returned from IDA* " << endl;
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
	const char path_actions[4] =    {'U', 'D', 'L', 'R'};

        for(auto it = path_to_goal.begin(); it!= path_to_goal.end(); ++it)
                cout << path_actions[*it] << " ";
 	cout << endl;
    }
    return 0;
}

