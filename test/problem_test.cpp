#include "problem.h"
#include <iostream>
#include <vector>

int main() {
    using namespace std;
    Problem test_problem;

    cout << "Initializing problem from file" << endl;
    State init_state = test_problem.init_from_file("test_level");

    cout << "Printing initial state" << endl;
    init_state.print();

    cout << "Checking if initial state is a goal" << endl;
    cout << test_problem.goal_test(&init_state) << endl;

    cout << "Getting available moves" << endl;
    vector<Action> actions = test_problem.valid_actions(&init_state);
    for (auto const& value: actions) {
        cout << value << " ";
    }
    cout << endl;

    cout << "Getting result of moving DOWN" << endl;
    State result_state = test_problem.result(&init_state, DOWN);
    result_state.print();

    cout << "Checking if result state is goal" << endl;
    cout << test_problem.goal_test(&result_state) << endl;

    return 0;
}
