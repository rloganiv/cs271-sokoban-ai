#include "state.h"
#include "ida_star.h"
#include "problem.h"
#include "state_space.h"

// Placeholder for including heuristic-related files

//#include <string>
#include <vector>
#include <stdlib.h>
#include <iostream>

// Temporary heuristic function - to be modified once heuristic classes are finalized
unsigned int h(State *state, unsigned int f)
{
	return (100-f)/10;
}

// Initialize cut-off bound of IDA* search to 0 and create goal, initial state objects
ida_star::ida_star()
{
	bound = 0;
	init_state = new State_Space;
	goal = new State_Space;
}

// Begin IDA* search from root node
std::vector<Action> ida_star::ida_begin(State root, Problem *test_problem)
{
	// Reset bound to the heuristic cost to reach the goal from the root
	bound = h(&root, 0); 
	unsigned int result;
	
	// Assign values to the initial state of the state space
	init_state->current = root;
	init_state->parent_to_curr = static_cast <Action> (-1);
	init_state->parent = NULL;
	
	while(true)
	{
		result = search(init_state, 0, test_problem); // IDA* search from the root
		if(result == 0) // Reached goal state
		{
			State_Space *traverse = new State_Space;
			traverse = goal;
			
			// Get the set of moves from goal to initial state
			while(traverse->parent != NULL)
			{
				path_to_goal.push_back(traverse->parent_to_curr);
				traverse = traverse->parent;
			}
			
			// Reverse the list to get the set of moves from initial state to goal
			std::reverse(path_to_goal.begin(), path_to_goal.end());
			return path_to_goal; 
		}
		
		if(result == UINT_MAX) // Not found a solution
		{
			path_to_goal.clear(); // Return empty vector of moves
			return path_to_goal;
		}
		bound = result;
	}
}

// Generate resultant states from making all valid actions from current state
std::vector<State_Space*> ida_star::generate_successors(State_Space *state, Problem *test_problem)
{
	// Get valid actions from current state
	std::vector<Action> actions = test_problem->valid_actions(&state->current);
	std::vector<State_Space*> gen_successors;
	
	for(std::vector<Action>::iterator it = actions.begin(); it!=actions.end(); ++it)
	{
		State_Space *next = new State_Space;	
		
		// Get and store the successors of current state
		next->current = test_problem->result(&state->current, *it);
		next->parent_to_curr = *it;
		next->parent = state;
		
		// Check if state is the goal and store it
		if(test_problem->goal_test(&next->current))
        		goal = next; 
		gen_successors.push_back(next);
				
	}
	return gen_successors;	
}

unsigned int ida_star::search(State_Space *state, unsigned int g, Problem *test_problem)
{
	// Calculate f value of the state
	unsigned int f = g + h(&state->current, g);
	
 	// Return f if f value is > cutoff bound
	if(f > bound)
		return f;

	// Return 0 if we have reached the goal state
	if(test_problem->goal_test(&state->current) == 1)
		return 0;

	
	std::vector<State_Space*> successors;
	unsigned int min = UINT_MAX, temp_result;

	// Generate successors of current state
	successors = generate_successors(state, test_problem);

	for(auto it = successors.begin(); it!=successors.end(); ++it)
	{
		// Recursive search - assuming unit cost for each move
		temp_result = search(*it, g+1, test_problem); 
		if(temp_result == 0) // Reached goal state
			return 0;
		if(temp_result < min) // Update bound
			min = temp_result;
	}
	return min;
}
