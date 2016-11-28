#include "problem.h"
#include "state_space.h"
#include "ida_star.h"
#include <iostream>
#include <vector>
#include "assignmentsolver.h"
#include "heuristic.h"
#include "bbsolver.h"

int main() {
    using namespace std;
    //Problem test_problem("courseTestFile");
    //Problem test_problem("std_suite/screen.1");
    //Problem test_problem("std_suite/screen.2");
    //Problem test_problem("addtl_test_suite/testFile2");
    Problem test_problem("addtl_test_suite/testFile3");
    //Problem test_problem("addtl_test_suite/microban3");
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
    path_to_goal = ida.ida_begin(*init_state, test_problem, solver);
    cout << "Returned from IDA* " << endl;

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

