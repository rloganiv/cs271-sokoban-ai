#ifndef PROBLEM_H
#define PROBLEM_H

#include "state.h"
#include <string>
#include <vector>

enum Action {
    UP,
    DOWN,
    LEFT,
    RIGHT
};

class Problem {
    public:
        // Set initial state and goal coordinates from file
        State init_from_file(std::string filename);

        // Get a vector of all actions that are valid in a given state
        std::vector<Action> valid_actions(State *state);

        // Compute the result of performing an action in the given state
        State result(State *state, Action action);

        // Check if given state is a goal state
        bool goal_test(State *state);

    private:
        // Vector of goal coordinates. Helps speed up goal test.
        std::vector<int> goal_coords;
};

#endif
