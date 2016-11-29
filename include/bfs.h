#ifndef BFS_H
#define BFS_H

#include "problem.h"
#include "state.h"
#include <vector>
#include "state_space.h"
#include "heuristic.h"
#include "assignmentsolver.h"
#include "bbsolver.h"
#include <queue>
#include <unordered_set>

class bfs {

	public:
		bfs();

		// Begin BFS search from the initial state
		std::vector<Action> bfs_begin(State &root, Problem &test_problem);

	private:

		// Store the Initial state and Goal state
		State_Space *init_state, *goal;

		// Store the set of moves to the goal
		std::vector<Action> path_to_goal;

		// Store the list of nodes to be visited in the frontier
		std::queue<State_Space> frontier;

		// Store the set of visited nodes
		std::unordered_set<State, StateHasher> visited;

};

#endif
