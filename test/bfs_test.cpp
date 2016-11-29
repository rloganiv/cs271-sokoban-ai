#include "problem.h"
#include "state_space.h"
//#include "ida_star.h"
#include <iostream>
#include <vector>
#include "bfs.h"
//#include "assignmentsolver.h"
//#include "heuristic.h"
//#include "bbsolver.h"

int main() {
    using namespace std;
   // Problem test_problem;
   // BBSolver solver;
    State *init_state;
    cout << "Initializing problem from file" << endl;
   // Problem test_problem("courseTestFile"); // Solves
   // Problem test_problem("std_suite/screen.1"); // Segmentation fault
   // Problem test_problem("addtl_test_suite/testFile2"); // Solves
   // Problem test_problem("addtl_test_suite/testFile3"); // Solves
    Problem test_problem("addtl_test_suite/microban3"); // Solves
    init_state = test_problem.get_init_state();
    cout << "Printing initial state" << endl;
    init_state->print();

    cout << "Checking if initial state is a goal" << endl;
    cout << test_problem.goal_test(init_state) << endl;

    cout << "Calling BFS" << endl;
    std::vector<Action> path_to_goal;

    bfs b;
    path_to_goal = b.bfs_begin(*init_state, test_problem);
    cout << "Returned from BFS " << endl;

    /*if(path_to_goal.empty())
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
    }*/
    return 0;
}

