#include "state.h"
#include "ida_star.h"
#include "problem.h"
#include "state_space.h"
#include "heuristic.h"
//#include "bbsolver.h"
//#include "assignmentsolver.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <climits>
#include <unordered_set>


// Temporary heuristic function - to be modified once heuristic classes are finalized
unsigned int h(State &state, unsigned int f)
{
	return (100-f)/10;
}


// Initialize cut-off bound of IDA* search to 0 and create goal, initial state objects
ida_star::ida_star()
{
	bound = 0;
	init_state = new State_Space;
	goal = new State_Space;
	//Heuristic heur;

}

// Begin IDA* search from root node
std::vector<Action> ida_star::ida_begin(State &root, Problem &test_problem, AssignmentSolver &solver)
{
	// Reset bound to the heuristic cost to reach the goal from the root
	Heuristic heur(&root, &solver);
	bound = heur.manhattan_dist_score(root);
	unsigned int result;
	
	// Assign values to the initial state of the state space
	init_state->current = root;
	init_state->parent_to_curr = static_cast <Action> (-1);
	init_state->parent = NULL;
	init_state->visited = false;	
	visited.insert(init_state->current);
	while(true)
	{
		//init_state->current.print();
		result = search(init_state, 0, test_problem, heur); // IDA* search from the root
		std::cout<<"Bound = "<<bound<<std::endl;
		
		visited.clear();
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


unsigned int ida_star::search(State_Space *state, unsigned int g, Problem &test_problem, Heuristic &heur)
{
	// Calculate f value of the state
	//unsigned int f = g + h(state->current, g); // Naive heuristic
	//unsigned int f = g + heur.evaluate(state->current); // Manhattan heuristic
	unsigned int f = g + heur.manhattan_dist_score(state->current);
	//unsigned int f = g; // UCS
 	
	std::cout<<"heuristic in search = "<<heur.manhattan_dist_score(state->current)<<"; f = "<<f<<std::endl;
	// Return f if f value is > cutoff bound
	state->current.print();
	std::cout<<std::endl;		

	if(f > bound)
		return f;

	// Return 0 if we have reached the goal state
	if(test_problem.goal_test(&state->current) == 1)
		return 0;

	unsigned int min = UINT_MAX, temp_result;

	// Generate successors of current state
	//State_Space *next = new State_Space;
	
	std::vector<Action> actions = test_problem.valid_actions(&state->current);
	if(actions.empty())
		return UINT_MAX;	

	for(std::vector<Action>::iterator it = actions.begin(); it!=actions.end(); ++it)
        {
                // Get and store the successors of current state
		State_Space *next = new State_Space;
                State s = test_problem.result(&state->current, *it);
                next->current = s;
		next->parent_to_curr = *it;
                next->parent = state;
                if(test_problem.goal_test(&next->current))
                        goal = next;

		if(!visited.count(next->current))
		{
			visited.insert(next->current);
			temp_result = search(next, (g+1), test_problem, heur);
		        if(temp_result == 0) // Reached goal state
                	   	return 0;
		        if(temp_result < min) // Update bound
        		        min = temp_result;
		}
		else
			std::cout<<"Already visited state"<<std::endl;
        }
	
	return min;
}
