#include "state.h"
#include "problem.h"
#include "state_space.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>
#include <unordered_set>
#include "bfs.h"
#include <list>

// Create initial state and goal state objects
bfs::bfs()
{
	init_state = new State_Space;
	goal = new State_Space;
	//Heuristic heur;

}

// Begin BFS search from root node
std::vector<Action> bfs::bfs_begin(State &root, Problem &test_problem)
{
	// Reset bound to the heuristic cost to reach the goal from the root
	unsigned int result;
	// Assign values to the initial state of the state space
	init_state->current = root;
	init_state->parent_to_curr = static_cast <Action> (-1);
	init_state->parent = NULL;
	init_state->visited = false;
	frontier.push(*init_state);
	visited.insert(init_state->current);
	std::list<State_Space> visiting;

	//std::cout << "Check = " << heur.manhattan_dist_score(init_state->current) << std::endl;
	while(!frontier.empty())
	{
		auto temp = frontier.front();
		visiting.push_back(frontier.front());
		frontier.pop();

		//std::cout << "In bfs_begin" << std::endl;
		//visiting.current.print();

		//std::vector<Action> actions = test_problem.valid_actions(&visiting.current);
		std::vector<Action> actions = test_problem.valid_actions(&temp.current);

		for(std::vector<Action>::iterator it = actions.begin(); it!=actions.end(); ++it)
	        {
			State_Space* next = new State_Space;
                	// Get and store the successors of current state
	                const State &s = test_problem.result(&temp.current, *it);
			next->current = s;
        	        next->parent_to_curr = *it;
			next->parent = &(visiting.back());
	                //std::cout << "Visiting - child" << *it << std::endl<<std::endl;
        	        //(next->current).print();
			// Check if state is the goal and store it
	                if(test_problem.goal_test(&next->current))
        	        {
				//std::cout<<"Reached the goal "<<std::endl;
		        	goal = next;
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

			if(!visited.count(next->current))
			{
//				std::cout<<"Inserted in frontier "<<std::endl;
				frontier.push(*next);
				visited.insert(next->current);
		   	}
//			else
//				std::cout<<"Already in frontier"<<std::endl;

       	}

	}

	path_to_goal.clear(); // Return empty vector of moves
        return path_to_goal;
}

