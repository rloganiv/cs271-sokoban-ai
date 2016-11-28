#include "problem.h"
#include "state_space.h"
#include "ida_star.h"
#include <iostream>
#include <vector>

int main() {
    using namespace std;
    Problem test_problem("courseTestFile");

    cout << "Initializing problem from file" << endl;
    State *init_state;
    init_state = test_problem.get_init_state();
    cout << "Printing initial state" << endl;
    init_state->print();

    cout << "Checking if initial state is a goal" << endl;
    cout << test_problem.goal_test(init_state) << endl;

    cout << "Calling IDA*" << endl;
    std::vector<Action> path_to_goal;

    ida_star ida;
    path_to_goal = ida.ida_begin(*init_state, &test_problem);
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

