#include "state.h"
#include "problem.h"
#include "state_space.h"

#include "heuristic.h"
#include "assignmentsolver.h"
#include "bbsolver.h"
#include <vector>
#include <stdlib.h>
#include <iostream>
#include <algorithm>
#include <climits>
#include <queue>
#include <unordered_map>
#include "a_star.h"
#include <list>

// Initialize cut-off bound of IDA* search to 0 and create goal, initial state objects
AStar::AStar()
{
	init_state = new State_Space;
	goal = new State_Space;
	//Heuristic heur;

}


// Begin A* search from root node
std::vector<Action> AStar::a_star_begin(State &root, Problem &test_problem, AssignmentSolver &solver)
{
	unsigned int result, fnew=0, g=0;
	Heuristic heur(&root, &solver);
	
	// Assign values to the initial state of the state space
	init_state->current = root;
	init_state->parent_to_curr = static_cast <Action> (-1);
	init_state->parent = NULL;
	init_state->f = heur.manhattan_dist_score(init_state->current);
	
	std::list<State_Space> visiting;	
	visited[init_state->current] = heur.manhattan_dist_score(init_state->current);
	
	std::vector<State_Space> frontier;
	frontier.push_back(*init_state);
	std::make_heap(frontier.begin(), frontier.end(), CompareState());
	

	//std::cout << "Check = " << heur.manhattan_dist_score(init_state->current) << std::endl;
	while(!frontier.empty())
	{
		auto temp = frontier.front();
		visiting.push_back(frontier.front());

		std::pop_heap(frontier.begin(), frontier.end(), CompareState()); 
		frontier.pop_back();

		std::cout<<std::endl<<"Current state: "<<std::endl;
		temp.current.print();

 		if(test_problem.goal_test(&temp.current))
        	{
			std::cout<<"Reached the goal "<<std::endl;
		       	goal = &temp;
			State_Space *traverse = new State_Space;
        	        traverse = goal;
                       	while(traverse->parent != NULL)
			{
        		        path_to_goal.push_back(traverse->parent_to_curr);
                                traverse = traverse->parent;
                        }
			
                        // Reverse the list to get the set of moves from initial state to goal
                       	std::reverse(path_to_goal.begin(), path_to_goal.end());
	                return path_to_goal;
	    	}

		std::vector<Action> actions = test_problem.valid_actions(&temp.current);
	
		for(std::vector<Action>::iterator it = actions.begin(); it!=actions.end(); ++it)
	        {
			State_Space* next = new State_Space;
		
			// Get and store the successors of current state
	                const State &s = test_problem.result(&temp.current, *it);
			next->current = s;
        	        next->parent_to_curr = *it;
			next->parent = &(visiting.back());
	 	       	fnew = g + 1 + heur.manhattan_dist_score(next->current);
			next->f = fnew;
	      		std::cout << "Visiting - child" << *it <<std::endl;
        	        (next->current).print();
			
			// Check if state has been visited before (and whether visited at a lower cost)
			if (!visited.count(next->current) || fnew < visited[next->current]) 
			{
				std::cout<<"Inserted in frontier "<<std::endl<<std::endl;
				frontier.push_back(*next);
				std::push_heap(frontier.begin(), frontier.end(), CompareState());
				visited[next->current] = fnew;
		   	}
			else
				std::cout<<"Already in frontier"<<std::endl;

        	}
	  g++; // Increment path cost

	}

	path_to_goal.clear(); // Return empty vector of moves
        return path_to_goal;
}

