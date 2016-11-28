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
        Problem(std::string filename);

        // Get a vector of all actions that are valid in a given state
        std::vector<Action> valid_actions(State *state);

        // Compute the result of performing an action in the given state
        State result(State *state, Action action);

        // Check if given state is a goal state
        bool goal_test(State *state);

        // Getters
        State* get_init_state();

    private:
        State* init_state;
        // Vector of goal coordinates. Helps speed up goal test.
        std::vector<int> goal_coords;
};

#endif
