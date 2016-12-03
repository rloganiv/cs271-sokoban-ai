#ifndef A_STAR_H
#define A_STAR_H

#include "problem.h"
#include "state.h"
#include <vector>
#include "state_space.h"
#include "heuristic.h"
#include "assignmentsolver.h"
#include "bbsolver.h"
#include <queue>
#include <unordered_map>
#include <list>

// Check if a state has been visited before at a lower cost
struct CompareState
{
    bool operator () (const State_Space& lhs, const State_Space& rhs) const
    {
        return lhs.f > rhs.f;
    }
};


class AStar {

	public:
		AStar();

		// Begin A* search from the initial state
		std::vector<Action> a_star_begin(State &root, Problem &test_problem, AssignmentSolver &solver);

	private:

		// Store the Initial state and Goal state
		State_Space *init_state, *goal;

		// Store the set of moves to the goal
		std::vector<Action> path_to_goal;

		// Store the list of nodes to be visited in the frontier
		std::priority_queue<State_Space, std::vector<State_Space>, CompareState> frontier;

		// Store the set of visited states
		std::unordered_map<State, unsigned int, StateHasher> visited;		

};

#endif
