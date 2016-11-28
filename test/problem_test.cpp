#include "problem.h"
#include <iostream>
#include <vector>

int main() {
    using namespace std;

    cout << "Initializing problem from file" << endl;
    Problem test_problem("std_suite/screen.1");

    cout << "Printing initial state" << endl;
    State * init_state;
    init_state = test_problem.get_init_state();
    init_state->print();

    cout << "Checking if initial state is a goal" << endl;
    cout << test_problem.goal_test(init_state) << endl;

    cout << "Getting available moves" << endl;
    vector<Action> actions = test_problem.valid_actions(init_state);
    for (auto const& value: actions) {
        cout << value << " ";
    }
    cout << endl;

    cout << "Getting result of moving UP" << endl;
    State result_state = test_problem.result(init_state, UP);
    result_state.print();

    return 0;
}
