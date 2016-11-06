#ifndef IDA_STAR_H
#define IDA_STAR_H

#include "problem.h"
#include "state.h"
#include <vector>
#include "state_space.h"

class ida_star {

	public:
		ida_star();
		
		// Begin IDA* search from the initial state
		std::vector<Action> ida_begin(State root, Problem *test_problem);

	private:
		// Bound for each search iteration
		unsigned int bound;

		// Recursive search from the successors of each state
		unsigned int search(State_Space *state, unsigned int g, Problem *test_problem);
		
		// Generate successors of current state
		std::vector<State_Space*> generate_successors(State_Space *state, Problem *test_problem);
		
		// Store the Initial state and Goal state
		State_Space *init_state, *goal;
		
		// Store the set of moves to the goal
		std::vector<Action> path_to_goal;
		
};

#endif
