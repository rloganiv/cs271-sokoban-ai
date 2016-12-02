#ifndef IDA_STAR_H
#define IDA_STAR_H

#include "problem.h"
#include "state.h"
#include <vector>
#include "state_space.h"
#include "heuristic.h"
#include "assignmentsolver.h"
#include "bbsolver.h"
#include <unordered_set>
#include <unordered_map>

class ida_star {

	public:
		ida_star();
		
		// Begin IDA* search from the initial state
		std::vector<Action> ida_begin(State &root, Problem &test_problem, AssignmentSolver &solver);

	private:
		// Bound for each search iteration
		unsigned int bound;

		// Recursive search from the successors of each state
		unsigned int search(State_Space *state, unsigned int g, Problem &test_problem, Heuristic &heur);
		
		// Store the Initial state and Goal state
		State_Space *init_state, *goal;
		
		// Store the set of moves to the goal
		std::vector<Action> path_to_goal;
		
		// Keep track of visited states
		//std::unordered_set<State, StateHasher> visited;
		std::unordered_map<State, unsigned int, StateHasher> visited;
		
};

#endif
